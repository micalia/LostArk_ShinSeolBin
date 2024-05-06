// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LostArkGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FHousingData
{
	GENERATED_USTRUCT_BODY()
public:
	FHousingData() : objClassName(""), objPos(FVector(0)), objRot(FRotator(0)) {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString objClassName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector objPos = FVector(0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator objRot = FRotator(0);
};

UCLASS()
class LOSTARK_API ULostArkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fullExp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currExp;

	////하우징 오브젝트 트랜스폼 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHousingData> housingDataArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> objClassNameString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> objClassPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRotator> objClassRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AActor*> assignObjDataArray;

	UFUNCTION(BlueprintCallable)
	void SaveAssignObjDatas();

};
