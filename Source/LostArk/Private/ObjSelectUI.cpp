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

UObjSelectUI::UObjSelectUI(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UObjSlot> tempSlot(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SB/UMG/WB_ObjSlot.WB_ObjSlot_C'"));
	if (tempSlot.Succeeded()) {
		objSlotFactory = tempSlot.Class;
	}

}

void UObjSelectUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/* 텍스트 사라짐 효과 구현 보류 "현재 위치에 배치할 수 없습니다" 메시지
	if (bCanNotAssignMsg) {
		disappearCurrTime += InDeltaTime;

		float opacity = disappearCurrTime / disappearDelayTime;
		CanNotAssignMsg->SetRenderOpacity(opacity);

		if (disappearCurrTime > disappearDelayTime) {
			disappearCurrTime = 0;
			bCanNotAssignMsg = false;
		}
	}*/
}

void UObjSelectUI::NativeConstruct()
{
	Super::NativeConstruct();

	//CanNotAssignMsg = Cast<UTextBlock>(GetWidgetFromName(TEXT("CanNotAssignMsg")));

	AHousingGameMode* gameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());
	FString noDataString = "";
	for (int i = 0; i < SlotCount; i++)
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
		else {
			objSlot->objNewData = FObjData(gameMode->objData[gameMode->objData.Num() - 1].objName, gameMode->objData[gameMode->objData.Num() - 1].objIcon, gameMode->objData[gameMode->objData.Num() - 1].objClassName, gameMode->objData[gameMode->objData.Num() - 1].objIsWallHang);
			int32 RowVal = i / SlotsPerRow;
			int32 ColumnVal = i % SlotsPerRow;
			UUniformGridSlot* NewGridPanel = UniformGridPanel->AddChildToUniformGrid(objSlot, RowVal, ColumnVal);
			NewGridPanel->SetHorizontalAlignment(HAlign_Fill);
			NewGridPanel->SetVerticalAlignment(VAlign_Fill);
		}
	}


}

