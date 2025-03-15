// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/CommonLibraryFunction.h"
#include "Pawns/RTS_PlayerController.h"

ARTS_PlayerController* UCommonLibraryFunction::GetMyController(const UObject* WorldContextObject)
{
	if(UWorld* World =  WorldContextObject->GetWorld())
	{
		return Cast<ARTS_PlayerController>(World->GetFirstPlayerController());
	}

	return nullptr;
}
