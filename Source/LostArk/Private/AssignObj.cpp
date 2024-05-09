// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignObj.h"
#include <Kismet/GameplayStatics.h>
#include "HousingGameMode.h"
#include "LostArk.h"

// Sets default values
AAssignObj::AAssignObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	RootComponent = rootComp;

	groupComp = CreateDefaultSubobject<USceneComponent>(TEXT("groupComp"));
	groupComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAssignObj::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());
	controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void AAssignObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//만약 레이트레이스 맞은 부분이 벽이라면 움직이지 않는다.
	if (bMove) {
		groupComp->SetRelativeScale3D(FVector(1.02));
		OverlapCheck();
		MoveObj();
	}
}

void AAssignObj::MoveObj()
{
	FVector WorldLocation;
	FVector WorldDirection;

	controller->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult HitResult;
	FVector StartLocation = WorldLocation;
	FVector EndLocation = StartLocation + (WorldDirection * 20000);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1);
	if (bHit)
	{
		if(HitResult.GetActor()){
			if (objNewData.objIsWallHang) {
				if (HitResult.GetActor()->GetName().Contains(TEXT("Wall1"))) {
					if (!bOverlapChk) {
						bCanAssign = true;
						GeneralMaterial();
					}
					SetActorRotation(gameMode->wall1Rotation);
				}
				else if (HitResult.GetActor()->GetName().Contains(TEXT("Wall2"))) {
					if (!bOverlapChk) {
						bCanAssign = true;
						GeneralMaterial();
					}
					SetActorRotation(gameMode->wall2Rotation);
				}
				else {	//벽이 아니라면
					bCanAssign = false;
					CanNotAssignMaterial();
				}
				HitLocation = HitResult.Location;
			}
			else { // 바닥에 배치할 오브젝트라면
				if (HitResult.GetActor()->ActorHasTag(TEXT("wall1"))) {
					bCanAssign = false;
					CanNotAssignMaterial();
				}
				else if (HitResult.GetActor()->ActorHasTag(TEXT("wall2"))) {
					bCanAssign = false;
					CanNotAssignMaterial();
				}
				else {	//벽이 아니라면				
					bMove = true;
					bCanAssign = true;
					GeneralMaterial();
					HitLocation = HitResult.Location;
				}
			}
		}
		SetActorLocation(HitLocation);
	}
}

void AAssignObj::CanNotAssignMaterial()
{//빨강
	if (DynamMat) {
		DynamMat->SetVectorParameterValue(TEXT("StateColor"),FLinearColor(1,0, 0.023153f,1));
	}
}

void AAssignObj::AssignSuccessMaterial()
{//초록
	if (DynamMat) {
		DynamMat->SetVectorParameterValue(TEXT("StateColor"), FLinearColor(0, 1, 0.124772f, 1));
	}
}

void AAssignObj::GeneralMaterial()
{
	if (!bOverlapChk) {
		if (DynamMat) {
			DynamMat->SetVectorParameterValue(TEXT("StateColor"), FLinearColor(1, 1, 1, 1));
		}
	}
}

void AAssignObj::OverlapCheck()
{
	if (overlapCount > 0) {
		bOverlapChk = true;
		CanNotAssignMaterial();
	}
	else {
		bOverlapChk = false;
	}
}

void AAssignObj::BeginOverlapCallFunc()
{ 
	if (bMove) {
		bOverlapChk = true;
		overlapCount++;
	}
}

void AAssignObj::EndOverlapCallFunc()
{
	if (bMove) {
		bOverlapChk = false;
		overlapCount--;
	}
}
