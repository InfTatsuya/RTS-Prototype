// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/SpawnerActor.h"
#include "Buildings/BuildingActor.h"
#include "GameInstance/RTS_GameInstance.h"
#include "Library/CommonLibraryFunction.h"
#include "Pawns/RTS_PlayerController.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnerActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!IsValid(CurrentBuilding)) return;

	if(ARTS_PlayerController* PlayerController = UCommonLibraryFunction::GetMyController(this))
	{
		FHitResult HitResult;
		if(PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult))
		{
			CurrentBuilding->SetActorLocation(HitResult.Location);
			CurrentBuilding->SetBuildingMaterial(bIsOverlapping ? RedMaterial : GreenMaterial);
		}
	}
}

void ASpawnerActor::OnReleasedBuidling()
{
	URTS_GameInstance* GameInstance = UCommonLibraryFunction::GetGameInstance(this);
	if(!GameInstance) return;

	GameInstance->UpdateResourceByBuilding(RequestedBuildingName);
	
	if(OriginalMaterial && CurrentBuilding)
	{
		CurrentBuilding->SetBuildingMaterial(OriginalMaterial);
		CurrentBuilding->StartConstruction();
	}
}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	if(BuildingActorClass)
	{
		CurrentBuilding = GetWorld()->SpawnActorDeferred<ABuildingActor>(BuildingActorClass, FTransform());
		CurrentBuilding->BuildingName = RequestedBuildingName;
		CurrentBuilding->FinishSpawning(FTransform());
		OriginalMaterial = CurrentBuilding->GetBuildingMaterial();
		
		CurrentBuilding->OnBuildingOverlappedDelegate.AddUObject(this, &ThisClass::SetOverlappingBool);
	}
}

void ASpawnerActor::SetOverlappingBool(bool bOverlapped)
{
	bIsOverlapping = bOverlapped;
}


