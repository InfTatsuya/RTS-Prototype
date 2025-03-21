// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/WorkerAnimInstance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interfaces/ResourcesInterface.h"
#include "Workers/WorkerCharacter.h"

void UWorkerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	WorkerCharacterRef = Cast<AWorkerCharacter>(TryGetPawnOwner());
}

void UWorkerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!IsValid(WorkerCharacterRef))
	{
		WorkerCharacterRef = Cast<AWorkerCharacter>(TryGetPawnOwner());
	}

	if(WorkerCharacterRef)
	{
		if(CurrentWorkerState != WorkerCharacterRef->CurrentState)
		{
			OnChangeState(WorkerCharacterRef->CurrentState);
		}
		
		CurrentWorkerState = WorkerCharacterRef->CurrentState;
	}
}

void UWorkerAnimInstance::OnNotifyChopEvent(int32 AmountToChop)
{
	if(!IsValid(WorkerCharacterRef)) return;

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(WorkerCharacterRef);
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	if(!AIController || !BBComponent) return;
	if(IWorkerInterface* WorkerInterface = Cast<IWorkerInterface>(WorkerCharacterRef))
	{
		WorkerInterface->ChangeCarryAmount(AmountToChop);
	}

	if(IResourcesInterface* ResourcesInterface = Cast<IResourcesInterface>(BBComponent->GetValueAsObject(FName("ResourceTarget"))))
	{
		if(ResourcesInterface->Deplete(AmountToChop))
		{
			BBComponent->SetValueAsEnum(FName("WorkerAction"), static_cast<UBlackboardKeyType_Enum::FDataType>(EWorkerState::EWS_Returning));
		}
	}
}

void UWorkerAnimInstance::OnChangeState(EWorkerState NewState) const
{
	switch (NewState) {
	case EWorkerState::EWS_Idle:
	case EWorkerState::EWS_Walking:
	case EWorkerState::EWS_Collecting:
		WorkerCharacterRef->ToggleToolResourceMesh(true, WorkerCharacterRef->ResourceType);
		break;
		
	case EWorkerState::EWS_Returning:
		WorkerCharacterRef->ToggleToolResourceMesh(false, WorkerCharacterRef->ResourceType);
		break;
		
	default:
		break;
	}
}
