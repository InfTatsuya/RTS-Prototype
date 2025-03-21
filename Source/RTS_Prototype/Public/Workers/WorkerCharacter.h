// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkerState.h"
#include "GameFramework/Character.h"
#include "Interfaces/WorkerInterface.h"
#include "WorkerCharacter.generated.h"

UCLASS()
class RTS_PROTOTYPE_API AWorkerCharacter : public ACharacter, public IWorkerInterface
{
	GENERATED_BODY()

public:
	
	AWorkerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EWorkerState CurrentState = EWorkerState::EWS_MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AResourceActor> ResourceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EResourceType ResourceType;
	
	//Implements WorkerInterface
	UFUNCTION(BlueprintCallable)
	virtual AResourceActor* GetNearestResource() override;

	virtual void ChangeCarryAmount(int32 Amount) override;

	virtual ABuildingActor* GetHome() override;

	virtual int32 GetCarryAmount() override;

	virtual EResourceType GetResourceType() override;
	
	//End Implements WorkerInterface

	void ToggleToolResourceMesh(bool bHoldTool, EResourceType ResourceType);
	void SetTool(EResourceType ResourceType);
	void SetCarryingResource(EResourceType ResourceType);
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	TObjectPtr<UStaticMeshComponent> ToolMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	TObjectPtr<UStaticMeshComponent> ResourceMesh;

private:

	UPROPERTY()
	int32 CarryAmount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABuildingActor> Home;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tools", meta = (AllowPrivateAccess = "true"))
	TMap<EResourceType, UStaticMesh*> ToolsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tools", meta = (AllowPrivateAccess = "true"))
	TMap<EResourceType, UStaticMesh*> ResourcesMap;

public:

	FORCEINLINE void SetHome(ABuildingActor* NewHome) { Home = NewHome; }

};
