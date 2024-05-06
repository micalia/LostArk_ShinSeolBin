// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UDialogue : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget),EditAnywhere, BlueprintReadWrite)
	class UTextBlock* TalkText;
};
