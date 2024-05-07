// Fill out your copyright notice in the Description page of Project Settings.


#include "HousingBaseUI.h"
#include <UMG/Public/Components/CanvasPanel.h>
#include "UMG/Public/Components/Button.h"
#include <HousingGameMode.h>
#include <HousingPlayer.h>
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"

UHousingBaseUI::UHousingBaseUI(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UHousingBaseUI::NativeConstruct() {
	Super::NativeConstruct(); 
	AssignBtn->OnClicked.AddDynamic(this, &UHousingBaseUI::HousingModeOn);

	for (TActorIterator<AHousingPlayer> it(GetWorld()); it; ++it) {
		HousingPlayer = *it;
	}
}

void UHousingBaseUI::HousingModeOn()
{
	AHousingGameMode* HousingGameMode = Cast<AHousingGameMode>(GetWorld()->GetAuthGameMode());
	if (HousingGameMode) {
		HousingGameMode->ClickAssignBtn();
		HousingPlayer->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	} 
}
