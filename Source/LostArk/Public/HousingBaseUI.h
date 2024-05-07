// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HousingBaseUI.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UHousingBaseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHousingBaseUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* HousingBasePanel;

	UPROPERTY(meta=(BindWidget))
	class UButton* AssignBtn;

	class AHousingPlayer* HousingPlayer;
	UFUNCTION()
	void HousingModeOn();
};
