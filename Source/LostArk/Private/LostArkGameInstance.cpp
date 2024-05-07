// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkGameInstance.h"
#include "AssignObj.h"
#include <Kismet/GameplayStatics.h>

void ULostArkGameInstance::SaveAssignObjDatas()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAssignObj::StaticClass(), assignObjDataArray);

	for (int i = 0; i < assignObjDataArray.Num(); i++)
	{
		AAssignObj* assingObj = Cast<AAssignObj>(assignObjDataArray[i]);
		FString objDataName = assingObj->objNewData.objClassName;
		FVector objDataPos = assingObj->GetActorLocation();
		FRotator objDataRot = assingObj->GetActorRotation();
		objClassNameString.Add(objDataName);
		objClassPos.Add(objDataPos);
		objClassRot.Add(objDataRot);
	}
}

