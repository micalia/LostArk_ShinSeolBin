// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HousingGameMode.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjSelectUI.generated.h"

/**
 *
 */
UCLASS()
class LOSTARK_API UObjSelectUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UObjSelectUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjData> objData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UObjSlot> objSlotFactory;

	UPROPERTY(EditAnywhere)
	int32 SlotsPerRow = 4;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UUniformGridPanel* UniformGridPanel;

	UPROPERTY(EditAnywhere)
	int32 SlotCount = 8;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ObjSelectUiPanel;

	class AHousingPlayer* HousingPlayer;
	class AHousingGameMode* gameMode;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnBtn;

	UFUNCTION()
	void HousingModeOff();
};
