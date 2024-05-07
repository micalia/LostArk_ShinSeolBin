// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HousingGameMode.h"
#include "ObjSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UObjSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FObjData objNewData;
	UPROPERTY(meta=(BindWidget))
	class UImage* SlotImage;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
