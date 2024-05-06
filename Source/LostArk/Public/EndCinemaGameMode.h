// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndCinemaGameMode.generated.h"

/**
 * 
 */
 //EndCinemaHousingGameMode에 사용되는 클래스
UCLASS()
class LOSTARK_API AEndCinemaGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> ObjActorArr;
		
		UFUNCTION(BlueprintCallable)
		void LoadAssignObjDatas();
};
