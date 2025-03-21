// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/WorkerAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Workers/WorkerState.h"

void AWorkerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsValid(BehaviorTreeClass))
	{
		RunBehaviorTree(BehaviorTreeClass);
		if(auto BlackboardRef = UAIBlueprintHelperLibrary::GetBlackboard(InPawn))
		{
			BlackboardRef->SetValueAsEnum(FName("WorkerAction"), static_cast<UBlackboardKeyType_Enum::FDataType>(EWorkerState::EWS_Idle));
		}
	}
}
