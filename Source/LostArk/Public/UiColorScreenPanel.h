// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UiColorScreenPanel.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UUiColorScreenPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	class UImage* ColorPanelimg;
};
