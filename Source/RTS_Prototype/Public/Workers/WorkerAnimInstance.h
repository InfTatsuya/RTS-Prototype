// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkerState.h"
#include "Animation/AnimInstance.h"
#include "WorkerAnimInstance.generated.h"

class AWorkerCharacter;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UWorkerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void OnNotifyChopEvent(int32 AmountToChop);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	EWorkerState CurrentWorkerState = EWorkerState::EWS_MAX;

	UPROPERTY()
	TObjectPtr<AWorkerCharacter> WorkerCharacterRef = nullptr;

	void OnChangeState(EWorkerState NewState) const;
	
};
