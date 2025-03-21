// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourcesEnum.h"
#include "UObject/Interface.h"
#include "WorkerInterface.generated.h"

class ABuildingActor;
class AResourceActor;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UWorkerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_PROTOTYPE_API IWorkerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual AResourceActor* GetNearestResource() = 0;

	virtual void ChangeCarryAmount(int32 Amount) = 0;

	virtual ABuildingActor* GetHome() = 0;

	virtual int32 GetCarryAmount() = 0;

	virtual EResourceType GetResourceType() = 0;
};
