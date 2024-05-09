// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjSelectUI.h"
#include "HousingGameMode.h"
#include "ObjSlot.h"
#include <UMG/Public/Components/UniformGridPanel.h>
#include <UMG/Public/Components/UniformGridSlot.h>
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include <Engine/World.h>
#include "AssignSettingUI.h"
#include <UMG/Public/Components/CanvasPanel.h>
#include <UMG/Public/Components/TextBlock.h>
#include <Layout/Geometry.h>
#include "LostArk.h"
#include "EngineUtils.h"
#include "UMG/Public/Components/Button.h"
#include "HousingPlayer.h"
#include "HousingBaseUI.h"
#include "Components/CapsuleComponent.h"

UObjSelectUI::UObjSelectUI(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UObjSlot> tempSlot(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_ObjSlot.WB_ObjSlot_C'"));
	if (tempSlot.Succeeded()) {
		objSlotFactory = tempSlot.Class;
	}
}

void UObjSelectUI::NativeConstruct()
{
	Super::NativeConstruct();

	for (TActorIterator<AHousingPlayer> it(GetWorld()); it; ++it) {
		HousingPlayer = *it;
	}

	gameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());
	if(gameMode == nullptr) return;

	ReturnBtn->OnClicked.AddDynamic(this, &UObjSelectUI::HousingModeOff);
	//UObjSelectUI::NativeConstruct()
	int32 ObjCount = gameMode->objData.Num() - 1;
	for (int i = 0; i < ObjCount; i++) //게임모드에서 읽어드린 데이터를 바탕으로 UI를 만듦
	{
		UObjSlot* objSlot = CreateWidget<UObjSlot>(GetWorld(), objSlotFactory);
		if (i < gameMode->objData.Num()) {
			objSlot->objNewData = FObjData(gameMode->objData[i].objName, gameMode->objData[i].objIcon, gameMode->objData[i].objClassName, gameMode->objData[i].objIsWallHang);
			int32 RowVal = i / SlotsPerRow;
			int32 ColumnVal = i % SlotsPerRow;
			UUniformGridSlot* NewGridPanel = UniformGridPanel->AddChildToUniformGrid(objSlot, RowVal, ColumnVal);
			NewGridPanel->SetHorizontalAlignment(HAlign_Fill);
			NewGridPanel->SetVerticalAlignment(VAlign_Fill);
		}
	}
	int EmptySlotCount = ObjCount % SlotsPerRow;
	if (EmptySlotCount > 0) { // 인벤토리가 빈 부분은 빈 슬롯으로 메꿈
		int ColumnFillSlot = SlotsPerRow - 1;
		for (int j = 0; j < EmptySlotCount; j++)
		{
			UObjSlot* objSlot = CreateWidget<UObjSlot>(GetWorld(), objSlotFactory);
			objSlot->objNewData = FObjData(gameMode->objData[gameMode->objData.Num() - 1].objName, gameMode->objData[gameMode->objData.Num() - 1].objIcon, gameMode->objData[gameMode->objData.Num() - 1].objClassName, gameMode->objData[gameMode->objData.Num() - 1].objIsWallHang);
			int32 RowVal = ObjCount / SlotsPerRow;
			int32 ColumnVal = ColumnFillSlot;
			ColumnFillSlot--;
			UUniformGridSlot* NewGridPanel = UniformGridPanel->AddChildToUniformGrid(objSlot, RowVal, ColumnVal);
			NewGridPanel->SetHorizontalAlignment(HAlign_Fill);
			NewGridPanel->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UObjSelectUI::HousingModeOff()
{
	SetVisibility(ESlateVisibility::Hidden);
	if (gameMode) {
		gameMode->housingBaseUI->SetVisibility(ESlateVisibility::Visible);
		gameMode->bAssignModeOn = false;
		gameMode->assignSettingUI->SetVisibility(ESlateVisibility::Hidden);
		gameMode->CustomModeOff();
		gameMode->bStartChangeColorPanel = true;
		gameMode->CancelCamMove();
		gameMode->AssignQuestSuccess(); 
		HousingPlayer->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
