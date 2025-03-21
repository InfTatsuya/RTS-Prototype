// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_SetHome.generated.h"

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UBTTask_SetHome : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:

	UBTTask_SetHome();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
