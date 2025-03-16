// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Resources/ResourcesEnum.h"
#include "CommonLibraryFunction.generated.h"

class URTS_GameInstance;
class ARTS_PlayerController;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UCommonLibraryFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ARTS_PlayerController* GetMyController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString GetResourceName(EResourceType Type);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static URTS_GameInstance* GetGameInstance(const UObject* WorldContextObject);
	
	static URTS_GameInstance* CachedGameInstance;
};
