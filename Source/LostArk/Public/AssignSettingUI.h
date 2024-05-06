// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AssignSettingUI.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UAssignSettingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	void NativeConstruct();

UPROPERTY()
	class AAssignObj* settingObj;

	UPROPERTY(EditAnywhere)
		float RotateSize = 20;
	UPROPERTY(EditAnywhere)
		float MicroRotateSize = 5;
		
		bool bMicroRotateMode;

	UFUNCTION(BlueprintCallable)
	virtual void RightRotate();
	UFUNCTION(BlueprintCallable)
		virtual void LeftRotate();
	UFUNCTION(BlueprintCallable)
		virtual void DeleteObj();
	UFUNCTION(BlueprintCallable)
		void MicroRotateMode();

		void InitRotateModeStyleAndVal();
		void RotateModeBtnStyle();
		void MicroRotateModeBtnStyle();

	UPROPERTY(meta=(BindWidget))
	class UHousingSystemButton* RotationRightBtn;
	UPROPERTY(meta=(BindWidget))
		class UHousingSystemButton* RotationLeftBtn;
	UPROPERTY(meta=(BindWidget))
		class UHousingSystemButton* DeleteObjBtn;
	UPROPERTY(meta=(BindWidget))
		class UHousingSystemButton* MoveObjBtn;
	UPROPERTY(meta = (BindWidget))
		class UHousingSystemButton* MicroRotationBtn;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ObjAngleTxt;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RightBtnTxt;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LeftBtnTxt;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DetailRotTxt;

	UPROPERTY()
	class AHousingGameMode* HousingGameMode;

	UFUNCTION()
	void DelObjMoveMode();
};
