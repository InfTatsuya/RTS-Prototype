// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/BTTask_SetHome.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Buildings/BuildingActor.h"
#include "Interfaces/WorkerInterface.h"

UBTTask_SetHome::UBTTask_SetHome()
{
	NodeName = TEXT("SetHome");
}

EBTNodeResult::Type UBTTask_SetHome::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	IWorkerInterface* WorkerInterface = Cast<IWorkerInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if(WorkerInterface == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("MoveLocation"), WorkerInterface->GetHome()->GetSpawnLocation());

	return EBTNodeResult::Succeeded;
}
