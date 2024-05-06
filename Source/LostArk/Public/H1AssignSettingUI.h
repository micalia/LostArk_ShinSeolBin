// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssignSettingUI.h"
#include "H1AssignSettingUI.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UH1AssignSettingUI : public UAssignSettingUI
{
	GENERATED_BODY()
	
public:
	void DeleteObj() override;
	void RightRotate() override;
	void LeftRotate() override;
};
