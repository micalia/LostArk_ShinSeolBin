// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HousingGameMode.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssignObj.generated.h"

UCLASS()
class LOSTARK_API AAssignObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssignObj();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	struct FObjData objNewData;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere)
		class USceneComponent* groupComp;

	UPROPERTY(BlueprintReadOnly)
	bool bMove = true;
	void MoveObj();

	UPROPERTY(BlueprintReadOnly)
	class AHousingGameMode* gameMode;

	UPROPERTY()
	APlayerController* controller;

	bool bCanAssign;

	UFUNCTION(BlueprintCallable)
	void CanNotAssignMaterial();
	void AssignSuccessMaterial();
	void GeneralMaterial();

	FVector HitLocation;

	UPROPERTY(BlueprintReadWrite)
	bool bOverlapChk;

	UPROPERTY(BlueprintReadWrite)
	class UMaterialInstanceDynamic* DynamMat;

	UPROPERTY(BlueprintReadWrite)
	int32 overlapCount;
	virtual void OverlapCheck();

	UFUNCTION(BlueprintCallable)
	void BeginOverlapCallFunc();
	UFUNCTION(BlueprintCallable)
	void EndOverlapCallFunc();

	UFUNCTION()
	void OnOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
