// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjSlot.h"
#include "HousingGameMode.h"

FReply UObjSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		AHousingGameMode* gameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode && gameMode->ChkSpawnObjActor()) {
			gameMode->ClickSound();
			gameMode->objClickData = objNewData;
			gameMode->SpawnObjActor();
		}
	}
	return FReply::Handled();
}