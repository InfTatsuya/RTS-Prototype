// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/BTTask_Arrived.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Workers/WorkerCharacter.h"

UBTTask_Arrived::UBTTask_Arrived()
{
	NodeName = TEXT("Arrived");
}

EBTNodeResult::Type UBTTask_Arrived::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// AWorkerCharacter* WorkerCharacter = Cast<AWorkerCharacter>(OwnerComp.GetAIOwner());
	// if(WorkerCharacter == nullptr)
	// {
	// 	return EBTNodeResult::Failed;
	// }

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName("WorkerAction"), static_cast<UBlackboardKeyType_Enum::FDataType>(EWorkerState::EWS_Collecting));

	return EBTNodeResult::Succeeded;
}
