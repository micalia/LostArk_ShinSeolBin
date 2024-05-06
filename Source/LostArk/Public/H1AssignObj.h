// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssignObj.h"
#include "H1AssignObj.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API AH1AssignObj : public AAssignObj
{
	GENERATED_BODY()

public:
	virtual void OverlapCheck() override;
};
