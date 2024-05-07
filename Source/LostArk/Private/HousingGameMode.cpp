// Fill out your copyright notice in the Description page of Project Settings.


#include "HousingGameMode.h"
#include "HousingBaseUI.h"
#include "ObjSelectUI.h"
#include <Kismet/GameplayStatics.h>
#include "AssignObj.h"
#include "LostArk.h"
#include "Wall.h"
#include "AssignSettingUI.h"
#include <UMG/Public/Components/CanvasPanelSlot.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/DefaultPawn.h>
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <MathUtil.h>
#include "UiColorScreenPanel.h"
#include <UMG/Public/Components/Image.h>
#include <UMG/Public/Components/TextBlock.h>
#include <Engine/LevelStreamingDynamic.h>
#include "HousingDoor.h"
#include <Sound/SoundBase.h>



AHousingGameMode::AHousingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UDataTable> tempData(TEXT("/Script/Engine.DataTable'/Game/SB/Assets/DT_InGameObjData.DT_InGameObjData'"));
	if (tempData.Succeeded())
	{
		UDataTable* data = tempData.Object;
		TArray<FName> rowNames = data->GetRowNames();
		for (int32 i = 0; i < rowNames.Num(); i++)
		{
			FObjData* objInfo = data->FindRow<FObjData>(rowNames[i], TEXT(""));
			objData.Add(*objInfo);
		}
	}

	static ConstructorHelpers::FClassFinder<UHousingBaseUI> tempBaseUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_HousingBaseUI.WB_HousingBaseUI_C'"));
	if (tempBaseUI.Succeeded()) {
		HousingBaseuiFactory = tempBaseUI.Class;
	}
	static ConstructorHelpers::FClassFinder<UObjSelectUI> tempObjSelectUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_ObjSelectUI.WB_ObjSelectUI_C'"));
	if (tempObjSelectUI.Succeeded()) {
		ObjSelectUiFactory = tempObjSelectUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UAssignSettingUI> tempAssignSettingUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_AssignSettingUI.WB_AssignSettingUI_C'"));
	if (tempAssignSettingUI.Succeeded()) {
		AssignSettingUIFactory = tempAssignSettingUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUiColorScreenPanel> tempUicolorScreenPanel(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_UiColorScreenPanel.WB_UiColorScreenPanel_C'"));
	if (tempUicolorScreenPanel.Succeeded()) {
		UiColorScreenPanelFactory = tempUicolorScreenPanel.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempClickSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/UI_mouse.UI_mouse'"));
	if (tempClickSound.Succeeded()) {
		clickSound = tempClickSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempRotateSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/object_rotation.object_rotation'"));
	if (tempRotateSound.Succeeded()) {
		rotateSound = tempRotateSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempObjAssignSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/Object_Assign.Object_Assign'"));
	if (tempObjAssignSound.Succeeded()) {
		objAssignSound = tempObjAssignSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempDeleteSound(TEXT("/Script/Engine.SoundWave'/Game/SB/Sounds/object_cancel.object_cancel'"));
	if (tempDeleteSound.Succeeded()) {
		deleteSound = tempDeleteSound.Object;
	}
}

void AHousingGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgets();

	controller = GetWorld()->GetFirstPlayerController();

	if (controller) {
		controller->InputComponent->BindAction("LeftClick", IE_Pressed, this, &AHousingGameMode::OnMouseLeftClick);
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWall::StaticClass(), foundWalls);

	for (int i = 0; i < foundWalls.Num(); i++)
	{
		bool foundWall1 = foundWalls[i]->GetName().Contains(TEXT("proto_BP_Wall1"));
		if (foundWall1) {
			wall1Rotation = foundWalls[i]->GetActorRotation();
		}
		bool foundWall2 = foundWalls[i]->GetName().Contains(TEXT("proto_BP_Wall2"));
		if (foundWall2) {
			wall2Rotation = foundWalls[i]->GetActorRotation();
		}
	}
}

void AHousingGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCamMove) {
		AssignModeStartCameraMove();
	}

	if (bStartChangeColorPanel) {
		OpacityDelayAndChangeOpacity();
	}
}

void AHousingGameMode::CreateWidgets()
{
	assignSettingUI = CreateWidget<UAssignSettingUI>(GetWorld(), AssignSettingUIFactory);
	if (assignSettingUI) {
		assignSettingUI->AddToViewport();
		assignSettingUI->SetVisibility(ESlateVisibility::Hidden);
	}

	housingBaseUI = CreateWidget<UHousingBaseUI>(GetWorld(), HousingBaseuiFactory);
	if (housingBaseUI) {
		housingBaseUI->AddToViewport(1);
		housingBaseUI->SetVisibility(ESlateVisibility::Hidden);
	}

	objSelectUI = CreateWidget<UObjSelectUI>(GetWorld(), ObjSelectUiFactory);
	if (objSelectUI) {
		objSelectUI->AddToViewport();
		objSelectUI->SetVisibility(ESlateVisibility::Hidden);
	}

	UiColorScreenPanelInstance = CreateWidget<UUiColorScreenPanel>(GetWorld(), UiColorScreenPanelFactory);
	if (UiColorScreenPanelInstance) {
		UiColorScreenPanelInstance->AddToViewport();
		UiColorScreenPanelInstance->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void AHousingGameMode::SpawnObjActor()
{
	for (int i = 0; i < ObjActorArr.Num(); i++)
	{
		if (ObjActorArr[i]->GetName().Equals(objClickData.objClassName)) {
			bAssignModeOn = true;
			bAssignMoveOn = true;
			if (bCustomMode) { 
				CustomModeOff();
			}
			selectObj = Cast<AAssignObj>(GetWorld()->SpawnActor<AActor>(ObjActorArr[i], FVector(0), FRotator(0)));
			selectObj->objNewData = objClickData;
			if (objClickData.objIsWallHang == true) {
				selectObj->SetActorRotation(wall1Rotation);
			}
			break;
		}

	}
}

bool AHousingGameMode::ChkSpawnObjActor()
{
	TArray<AActor*> assinObjsArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAssignObj::StaticClass(), assinObjsArr);
	for (int i =0; i < assinObjsArr.Num();i++)
	{
		if (assinObjsArr[i]) {
			AAssignObj* assignObj = Cast<AAssignObj>(assinObjsArr[i]);
			if (assignObj) {
				if (assignObj->bMove) {
					return false;
					break;
				}
			}
		}
	}

	return true;
}

void AHousingGameMode::ClickAssignBtn()
{
	bAssignModeOn = true;
	housingBaseUI->SetVisibility(ESlateVisibility::Hidden);
	objSelectUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	bCamMove = true;
}

void AHousingGameMode::OnMouseLeftClick()
{
	if (bAssignModeOn) { 
		UGameplayStatics::PlaySound2D(GetWorld(),clickSound);
		if (bAssignMoveOn || bCustomMode == true) {
			if (selectObj) {
				if(selectObj->bOverlapChk) return;
				if (selectObj->bMove == false && bCustomMode == false) {
					selectObj->bMove = true;
				}
				else {
					if (selectObj->bCanAssign) {
						if (bCustomMode == false) {
							CustomModeOn();
						}
						else {
							CustomModeOff();
						}
					}
				}
			}
		}
		else {
			FVector WorldLocation;
			FVector WorldDirection;

			controller->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

			FHitResult HitResult;
			FVector StartLocation = WorldLocation;
			FVector EndLocation = StartLocation + (WorldDirection * 20000);

			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel11);

			if (bHit)
			{
				AAssignObj* assignObj = Cast<AAssignObj>(HitResult.GetActor());
				if (assignObj) {
					selectObj = assignObj;
					CustomModeOn();
				}
			}
		}
	}

}

void AHousingGameMode::CustomModeOn()
{
	bCustomMode = true;
	if (selectObj) {
		selectObj->AssignSuccessMaterial();
		if (selectObj->bMove) {
			UGameplayStatics::PlaySound2D(GetWorld(), objAssignSound);
		}
		selectObj->bMove = false;
		selectObj->groupComp->SetRelativeScale3D(FVector(1));
	}
	FVector2D ScreenLocation;

	bool bResult = UGameplayStatics::ProjectWorldToScreen(controller, selectObj->GetActorLocation(), ScreenLocation);
	if (bResult) {
		if (assignSettingUI) {
			assignSettingUI->settingObj = selectObj;
			InitObjRotationTxtUI();

			assignSettingUI->SetPositionInViewport(ScreenLocation);
			assignSettingUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
	bAssignMoveOn = false;

}

void AHousingGameMode::CustomModeOff()
{
	bCustomMode = false;
	if (selectObj) {
		selectObj->GeneralMaterial();
	}
	if (assignSettingUI) {
		assignSettingUI->SetVisibility(ESlateVisibility::Hidden);
		assignSettingUI->InitRotateModeStyleAndVal();
	}
}

void AHousingGameMode::ObjMoveMode()
{
	bCustomMode = false;
	bAssignMoveOn = true;
	selectObj->bMove = true;
	selectObj->GeneralMaterial();
	assignSettingUI->SetVisibility(ESlateVisibility::Hidden);
}

float AHousingGameMode::easeInOutCubic(float value)
{
	return value < 0.5 ? 4 * value * value * value : 1 - UKismetMathLibrary::MultiplyMultiply_FloatFloat(-2 * value + 2, 3) / 2;
}

void AHousingGameMode::InitSpringArmLength()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		AActor* CameraOwner = PlayerController->GetViewTarget();
		if (CameraOwner)
		{
			ACharacter* player = Cast<ACharacter>(CameraOwner);
			if (player)
			{
				cam = Cast<USpringArmComponent>(player->FindComponentByClass(USpringArmComponent::StaticClass()));
				if (cam) {
					OriginCamSpringArmLength = cam->TargetArmLength;
					EndCamSpringArmLength = OriginCamSpringArmLength + addSpringArmLengthVal;
				}
			}
		}
	}
}

void AHousingGameMode::AssignModeStartCameraMove()
{
	camMoveCurrTime+=GetWorld()->GetDeltaSeconds();
	float alpha = camMoveCurrTime/camMoveTime;
	if (alpha > 1) {
		camMoveCurrTime = 0;
		bCamMove = false;
		alpha = 1;
		if (cam) {
			cam->TargetArmLength = FMathf::Lerp(OriginCamSpringArmLength, EndCamSpringArmLength, easeInOutCubic(alpha));
		}
	}
	else {
		if (cam) {
			cam->TargetArmLength = FMathf::Lerp(OriginCamSpringArmLength, EndCamSpringArmLength, easeInOutCubic(alpha));
		}
	}
}

void AHousingGameMode::CancelCamMove()
{
	if (cam) {
		cam->TargetArmLength = OriginCamSpringArmLength;
		camMoveCurrTime = 0;
		bCamMove = false;
	}
}

void AHousingGameMode::OpacityDelayAndChangeOpacity()
{
	opacityDelayCurrTime+=GetWorld()->GetDeltaSeconds();
	UiColorScreenPanelInstance->ColorPanelimg->SetRenderOpacity(1);
	if (opacityDelayCurrTime > opacityDelayTime) {
		ChangeOpacityColorPanel();
	}
}

void AHousingGameMode::ChangeOpacityColorPanel()
{
	if (UiColorScreenPanelInstance) {
		opacityCurrTime+=GetWorld()->GetDeltaSeconds();

		float alpha = opacityCurrTime / opacityChangeTime;
			UiColorScreenPanelInstance->ColorPanelimg->SetRenderOpacity(FMathf::Lerp(1, 0, alpha));
		
		if (opacityCurrTime > opacityChangeTime) {
			opacityDelayCurrTime=0;
			opacityCurrTime = 0;
			bStartChangeColorPanel = false; 
		}
	}
}

void AHousingGameMode::InitObjRotationTxtUI()
{
	if (selectObj->objNewData.objIsWallHang) {
		FString YawString = FString::Printf(TEXT("%d%c"), 0, 0xB0);
		assignSettingUI->ObjAngleTxt->SetText(FText::FromString(YawString));
	}
	else {
		FRotator originRot = assignSettingUI->settingObj->rootComp->GetComponentRotation();

		float YawValue;
		float NormalizedYawValue;
		YawValue = originRot.Yaw;
		NormalizedYawValue = FMath::Fmod(YawValue, 360.0f);
		if (NormalizedYawValue < 0)
		{
			NormalizedYawValue += 360.0f;
		}

		FString YawString = FString::Printf(TEXT("%.f%c"), NormalizedYawValue, 0xB0);
		assignSettingUI->ObjAngleTxt->SetText(FText::FromString(YawString));
	}
}

void AHousingGameMode::OnLevelStreamingComplete()
{
	InitHousingDoor();
}
