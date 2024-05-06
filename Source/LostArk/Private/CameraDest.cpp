// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDest.h"

// Sets default values
ACameraDest::ACameraDest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	RootComponent = rootComp;
}

// Called when the game starts or when spawned
void ACameraDest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

