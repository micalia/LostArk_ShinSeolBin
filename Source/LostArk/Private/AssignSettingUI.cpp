// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignSettingUI.h"
#include "AssignObj.h"
#include "LostArk.h"
#include <UMG/Public/Components/Button.h>
#include "HousingGameMode.h"
#include "HousingSystemButton.h"
#include <UMG/Public/Components/TextBlock.h>
#include <Internationalization/Text.h>
#include <Kismet/GameplayStatics.h>

void UAssignSettingUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RotationRightBtn = Cast<UHousingSystemButton>(GetWidgetFromName(TEXT("RotationRightBtn")));
	RotationRightBtn->InitButton();

	RotationLeftBtn = Cast<UHousingSystemButton>(GetWidgetFromName(TEXT("RotationLeftBtn")));
	RotationLeftBtn->InitButton();

	DeleteObjBtn = Cast<UHousingSystemButton>(GetWidgetFromName(TEXT("DeleteObjBtn")));
	DeleteObjBtn->InitButton();

	MoveObjBtn = Cast<UHousingSystemButton>(GetWidgetFromName(TEXT("MoveObjBtn")));
	MoveObjBtn->InitButton();

	MicroRotationBtn = Cast<UHousingSystemButton>(GetWidgetFromName(TEXT("MicroRotationBtn")));
	MicroRotationBtn->InitButton();

	ObjAngleTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("ObjAngleTxt")));
	RightBtnTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("RightBtnTxt")));
	LeftBtnTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("LeftBtnTxt")));
	DetailRotTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("DetailRotTxt")));
}

void UAssignSettingUI::NativeConstruct()
{
	Super::NativeConstruct();

	HousingGameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());

	RotationRightBtn->OnClicked.AddDynamic(this, &UAssignSettingUI::RightRotate);
	RotationLeftBtn->OnClicked.AddDynamic(this, &UAssignSettingUI::LeftRotate);
	DeleteObjBtn->OnClicked.AddDynamic(this, &UAssignSettingUI::DeleteObj);
	MoveObjBtn->OnClicked.AddDynamic(HousingGameMode, &AHousingGameMode::ObjMoveMode);
	MicroRotationBtn->OnClicked.AddDynamic(this, &UAssignSettingUI::MicroRotateMode);

}

void UAssignSettingUI::RightRotate()
{
	if (HousingGameMode) {
		UGameplayStatics::PlaySound2D(GetWorld(),HousingGameMode->rotateSound);
	}
	if(settingObj->objNewData.objIsWallHang) return;
	FRotator originRot = settingObj->rootComp->GetComponentRotation();
	float YawValue;
	float NormalizedYawValue;

	if (bMicroRotateMode) {
		originRot.Yaw = originRot.Yaw + MicroRotateSize;
		YawValue = originRot.Yaw;
		NormalizedYawValue = FMath::Fmod(YawValue, 360.0f);
		if (NormalizedYawValue < 0)
		{
			NormalizedYawValue += 360.0f;
		}
	}
	else {
		originRot.Yaw = originRot.Yaw + RotateSize;
		YawValue = originRot.Yaw;
		NormalizedYawValue = FMath::Fmod(YawValue, 360.0f);
		if (NormalizedYawValue < 0)
		{
			NormalizedYawValue += 360.0f; 
		}
	}
	FString YawString = FString::Printf(TEXT("%.f%c"), NormalizedYawValue, 0xB0);
	ObjAngleTxt->SetText(FText::FromString(YawString));
	settingObj->rootComp->SetRelativeRotation(originRot);
}

void UAssignSettingUI::LeftRotate()
{
	if (HousingGameMode) {
		UGameplayStatics::PlaySound2D(GetWorld(), HousingGameMode->rotateSound);
	}
	if (settingObj->objNewData.objIsWallHang) return;
	FRotator originRot = settingObj->rootComp->GetComponentRotation();
	float YawValue;
	float NormalizedYawValue;
	// UAssignSettingUI::LeftRotate()
	if (bMicroRotateMode) { // 일반 회전 모드 : 20도 씩 회전
		originRot.Yaw = originRot.Yaw - MicroRotateSize; 
		YawValue = originRot.Yaw;
		NormalizedYawValue = FMath::Fmod(YawValue, 360.0f);
		if (NormalizedYawValue < 0)
		{
			NormalizedYawValue += 360.0f; 
		}
	}
	else { // 미세 회전 모드 : 5도 씩 회전
		originRot.Yaw = originRot.Yaw - RotateSize;
		YawValue = originRot.Yaw;
		NormalizedYawValue = FMath::Fmod(YawValue, 360.0f);
		if (NormalizedYawValue < 0)
		{
			NormalizedYawValue += 360.0f;
		}
	}														// 0xB0 => 각도 기호
	FString YawString = FString::Printf(TEXT("%.f%c"), NormalizedYawValue, 0xB0);
	ObjAngleTxt->SetText(FText::FromString(YawString));
	settingObj->rootComp->SetRelativeRotation(originRot); // 오브젝트 회전
}

void UAssignSettingUI::DeleteObj()
{
	if (settingObj) {
		settingObj->Destroy();
	}
	if (HousingGameMode) {
		UGameplayStatics::PlaySound2D(GetWorld(), HousingGameMode->deleteSound);
		HousingGameMode->CustomModeOff();
	}
}

void UAssignSettingUI::MicroRotateMode()
{
	if(settingObj->objNewData.objIsWallHang)return;
	if (bMicroRotateMode) {
		bMicroRotateMode = false;
		RotateModeBtnStyle();
	}
	else {
		bMicroRotateMode = true;
		MicroRotateModeBtnStyle();
	}
}

void UAssignSettingUI::InitRotateModeStyleAndVal()
{
	bMicroRotateMode = false;
	RotateModeBtnStyle();
}

void UAssignSettingUI::RotateModeBtnStyle()
{
	MicroRotationBtn->SetBackgroundColor(FLinearColor(0.287441f, 0.552012f, 1, 1));
	RotationLeftBtn->SetBackgroundColor(FLinearColor(0.287441f, 0.552012f, 1, 1));
	RotationRightBtn->SetBackgroundColor(FLinearColor(0.287441f, 0.552012f, 1, 1));

	FString LeftRotBtn = FString::Printf(TEXT("회전(E)"));
	LeftBtnTxt->SetText(FText::FromString(LeftRotBtn));
	LeftBtnTxt->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	FString RightRotBtn = FString::Printf(TEXT("회전(Q)"));
	RightBtnTxt->SetText(FText::FromString(RightRotBtn));
	RightBtnTxt->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));

	DetailRotTxt->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

void UAssignSettingUI::MicroRotateModeBtnStyle()
{
	MicroRotationBtn->SetBackgroundColor(FLinearColor(1, 0.924858f, 0, 1));
	RotationLeftBtn->SetBackgroundColor(FLinearColor(1, 0.924858f, 0, 1));
	RotationRightBtn->SetBackgroundColor(FLinearColor(1, 0.924858f, 0, 1));

	FString LeftRotBtn = FString::Printf(TEXT("미세 회전(E)"));
	LeftBtnTxt->SetText(FText::FromString(LeftRotBtn));
	LeftBtnTxt->SetColorAndOpacity(FLinearColor(1, 0.888391,0,1));
	FString RightRotBtn = FString::Printf(TEXT("미세 회전(Q)"));
	RightBtnTxt->SetText(FText::FromString(RightRotBtn));
	RightBtnTxt->SetColorAndOpacity(FLinearColor(1, 0.888391, 0, 1));

	DetailRotTxt->SetColorAndOpacity(FLinearColor(1, 0.888391, 0, 1));
}

void UAssignSettingUI::DelObjMoveMode()
{
	HousingGameMode->ObjMoveMode();
}
