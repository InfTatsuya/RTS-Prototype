// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

class ABuildingActor;

UCLASS()
class RTS_PROTOTYPE_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnerActor();

	UPROPERTY()
	FName RequestedBuildingName;

	virtual void Tick(float DeltaSeconds) override;

	void OnReleasedBuidling();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
	TSubclassOf<ABuildingActor> BuildingActorClass;

private:

	void SetOverlappingBool(bool bOverlapped);

	UPROPERTY()
	TObjectPtr<ABuildingActor> CurrentBuilding = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsOverlapping = false;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> GreenMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> RedMaterial;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> OriginalMaterial;

public:

	FORCEINLINE bool IsOverlapping() const { return bIsOverlapping; }
};
