// Fill out your copyright notice in the Description page of Project Settings.


#include "HousingDoor.h"

// Sets default values
AHousingDoor::AHousingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHousingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHousingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

