// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/CommonLibraryFunction.h"

#include "GameInstance/RTS_GameInstance.h"
#include "Pawns/RTS_PlayerController.h"

URTS_GameInstance* UCommonLibraryFunction::CachedGameInstance = nullptr;

ARTS_PlayerController* UCommonLibraryFunction::GetMyController(const UObject* WorldContextObject)
{
	if(UWorld* World =  WorldContextObject->GetWorld())
	{
		return Cast<ARTS_PlayerController>(World->GetFirstPlayerController());
	}

	return nullptr;
}

FString UCommonLibraryFunction::GetResourceName(EResourceType Type)
{
	switch (Type)
	{
	case EResourceType::ERT_Wood:
		return FString("Wood");
		
	case EResourceType::ERT_Rock:
		return FString("Rock");
		
	case EResourceType::ERT_Money:
		return FString("Money");
	}

	return FString();
}

URTS_GameInstance* UCommonLibraryFunction::GetGameInstance(const UObject* WorldContextObject)
{
	if(IsValid(CachedGameInstance)) return CachedGameInstance;
	
	if(UWorld* World =  WorldContextObject->GetWorld())
	{
		CachedGameInstance = Cast<URTS_GameInstance>(World->GetGameInstance());
		return CachedGameInstance;
	}
	
	return nullptr;
}
