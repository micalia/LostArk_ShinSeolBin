// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Engine/DataTable.h>
#include "HousingGameMode.generated.h"

class ULevelStreamingDynamic;

USTRUCT(BlueprintType)
struct FObjData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FObjData() : objName(""), objIcon(nullptr), objClassName(""), objIsWallHang(false) {};
	FObjData(FString& name, UTexture2D* icon, FString& ClassName, bool isWallHang) : objName(name), objIcon(icon), objClassName(ClassName), objIsWallHang(isWallHang) {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString objName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* objIcon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString objClassName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool objIsWallHang = false;
};

UCLASS()
class LOSTARK_API AHousingGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHousingDoor* housingDoor;

	AHousingGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void CreateWidgets();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FObjData> objData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FObjData objClickData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> ObjActorArr;

	UFUNCTION(BlueprintCallable)
		void SpawnObjActor();

	UFUNCTION(BlueprintCallable)
		bool ChkSpawnObjActor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UHousingBaseUI> HousingBaseuiFactory;

	UPROPERTY(BlueprintReadWrite)
		class UHousingBaseUI* housingBaseUI;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UObjSelectUI> ObjSelectUiFactory;

	UPROPERTY(BlueprintReadWrite)
		class UObjSelectUI* objSelectUI;

	UFUNCTION(BlueprintCallable)
		void ClickAssignBtn();

	UPROPERTY(BlueprintReadWrite)
		bool bAssignModeOn;
	bool bAssignMoveOn;

	UPROPERTY()
		class AAssignObj* selectObj;

	UFUNCTION()
		virtual void OnMouseLeftClick();

	UPROPERTY()
		FRotator wall1Rotation;
	UPROPERTY()
		FRotator wall2Rotation;

	UPROPERTY()
		TArray<AActor*> foundWalls;

	UPROPERTY()
		APlayerController* controller;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UAssignSettingUI> AssignSettingUIFactory;

	UPROPERTY(BlueprintReadWrite)
		class UAssignSettingUI* assignSettingUI;

	UPROPERTY(BlueprintReadWrite)
		bool bCustomMode;
	void CustomModeOn();
	UFUNCTION(BlueprintCallable)
		void CustomModeOff();

	UFUNCTION(BlueprintCallable)
		void ObjMoveMode();
	//*******************************//
	//시작시 카메라 무브
	UPROPERTY(BlueprintReadOnly)
		class USpringArmComponent* cam;
	UFUNCTION(BlueprintCallable)
	float easeInOutCubic(float value);

	bool bCamMove;
	UFUNCTION(BlueprintCallable)
	void InitSpringArmLength();
	UPROPERTY(BlueprintReadOnly)
	float OriginCamSpringArmLength;
	float EndCamSpringArmLength;
	void AssignModeStartCameraMove();
	float camMoveCurrTime;
	UPROPERTY(EditAnywhere, Category = "CamMove")
		float camMoveTime = 1.5;
	UPROPERTY(EditAnywhere, Category = "CamMove")
		float addSpringArmLengthVal = 300;
		UFUNCTION(BlueprintCallable)
		void CancelCamMove();
	//*******************************//
	TSubclassOf<class UUiColorScreenPanel> UiColorScreenPanelFactory;
	UPROPERTY()
	class UUiColorScreenPanel* UiColorScreenPanelInstance;
	UPROPERTY(BlueprintReadWrite)
	bool bStartChangeColorPanel;
	UPROPERTY(BlueprintReadWrite)
	bool bOpacityDelayStart;
	float opacityDelayCurrTime;
	UPROPERTY(EditAnywhere, Category = "CustomMode")
	float opacityDelayTime = 0.2f;
	void OpacityDelayAndChangeOpacity();
	//**//
	float opacityCurrTime;
	UPROPERTY(EditAnywhere, Category="CustomMode")
	float opacityChangeTime = 1;
	void ChangeOpacityColorPanel();
	//*******************************//

	void InitObjRotationTxtUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AssignQuestSuccess();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RestoreCamPos();

	UFUNCTION()
    void OnLevelStreamingComplete();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitHousingDoor();

	//****************************//
	//Sound
	//****************************//
	UPROPERTY(EditAnywhere, Category="Sound")
		class USoundBase* objAssignSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* clickSound;
	UPROPERTY(EditAnywhere, Category="Sound")
	class USoundBase* rotateSound;
	UPROPERTY(EditAnywhere, Category="Sound")
	class USoundBase* deleteSound;

	void ClickSound();

	// 레벨 로딩 완료 콜백 함수
    UFUNCTION()
    void OnSubLevelLoaded();

private:
    // 로딩된 레벨 인스턴스를 저장하고 싶다면 여기에 포인터를 보관할 수 있음
    UPROPERTY()
    ULevelStreamingDynamic* LoadedLevelInstance;
};
