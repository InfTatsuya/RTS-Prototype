// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonLibraryFunction.generated.h"

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
};
