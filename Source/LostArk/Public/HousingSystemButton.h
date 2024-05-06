// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HousingSystemButton.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UHousingSystemButton : public UButton
{
	GENERATED_BODY()
public:
	UHousingSystemButton();

	void InitButton();
};
