// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HousingGameMode.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UObjSelectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UObjSelectUI(const FObjectInitializer &ObjectInitializer);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjData> objData;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UObjSlot> objSlotFactory;

	UPROPERTY(EditAnywhere)
	int32 SlotsPerRow = 4;

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	class UUniformGridPanel* UniformGridPanel;

	UPROPERTY(EditAnywhere)
	int32 SlotCount=8;

		UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* ObjSelectUiPanel;

	///////////////////
	// 오브젝트 배치할 수 없음 텍스트 opacity 사라짐 효과 구현 보류
	//////////////////
	/*UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	class UTextBlock* CanNotAssignMsg;

	bool bCanNotAssignMsg;
	float disappearCurrTime;
	float disappearDelayTime = 3;
	*/
};
