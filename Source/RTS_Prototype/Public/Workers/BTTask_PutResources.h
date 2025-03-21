// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_PutResources.generated.h"

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UBTTask_PutResources : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:

	UBTTask_PutResources();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool PutResourceOnFinished(UBehaviorTreeComponent& OwnerComp);
};
