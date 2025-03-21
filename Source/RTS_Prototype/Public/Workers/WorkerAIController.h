// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WorkerAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API AWorkerAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BehaviorTree")
	TObjectPtr<UBehaviorTree> BehaviorTreeClass;
};
