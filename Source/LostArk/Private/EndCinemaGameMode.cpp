// Fill out your copyright notice in the Description page of Project Settings.


#include "EndCinemaGameMode.h"
#include "LostArkGameInstance.h"
#include "AssignObj.h"

void AEndCinemaGameMode::LoadAssignObjDatas()
{
	ULostArkGameInstance* gameInstance = Cast<ULostArkGameInstance>(GetGameInstance());

	if (gameInstance) {
		for (int i = 0; i < gameInstance->objClassNameString.Num(); i++)
		{
			for (int j = 0; j < ObjActorArr.Num(); j++)
			{
				if (ObjActorArr[j]->GetName().Equals(gameInstance->objClassNameString[i])) {
					AAssignObj* assingObj = Cast<AAssignObj>(GetWorld()->SpawnActor<AActor>(ObjActorArr[j], gameInstance->objClassPos[i], gameInstance->objClassRot[i]));
					break;
				}
			}

		}
	}
}
