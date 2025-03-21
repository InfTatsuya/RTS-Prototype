// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/BTTask_PutResources.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "GameInstance/RTS_GameInstance.h"
#include "Interfaces/WorkerInterface.h"
#include "Library/CommonLibraryFunction.h"
#include "Navigation/PathFollowingComponent.h"
#include "Resources/ResourcesEnum.h"
#include "Workers/WorkerState.h"

UBTTask_PutResources::UBTTask_PutResources()
{
	NodeName = TEXT("PutResources");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_PutResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("MoveLocation")));
	MoveRequest.SetAcceptanceRadius(20.f);
	FPathFollowingRequestResult MoveResult = OwnerComp.GetAIOwner()->MoveTo(MoveRequest);

	UE_LOG(LogTemp, Warning, TEXT("MoveResult: %s"), *UEnum::GetValueAsString(MoveResult.Code));

	if(MoveResult.Code == EPathFollowingRequestResult::Failed) return EBTNodeResult::Failed;
	if(MoveResult.Code == EPathFollowingRequestResult::RequestSuccessful) return EBTNodeResult::InProgress;

	if(PutResourceOnFinished(OwnerComp))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_PutResources::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControlledPawn == nullptr)
	{
		return;
	}
	
	const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("MoveLocation"));
	const float Distance = (TargetLocation - ControlledPawn->GetActorLocation()).Length();
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);
	if(Distance < 50.f)
	{
		PutResourceOnFinished(OwnerComp);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

bool UBTTask_PutResources::PutResourceOnFinished(UBehaviorTreeComponent& OwnerComp)
{
	UE_LOG(LogTemp, Warning, TEXT("PutResourceOnFinished Called"));
	
	if(IWorkerInterface* WorkerInterface = Cast<IWorkerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EResourceType ResourceType = WorkerInterface->GetResourceType();
		int32 ResourceAmount = WorkerInterface->GetCarryAmount();

		UCommonLibraryFunction::GetGameInstance(OwnerComp.GetAIOwner()->GetPawn())->AlterResource(ResourceType, ResourceAmount);
		WorkerInterface->ChangeCarryAmount(-ResourceAmount);

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName("WorkerAction"), static_cast<UBlackboardKeyType_Enum::FDataType>(EWorkerState::EWS_Idle));

		return true;
	}

	return false;
}
