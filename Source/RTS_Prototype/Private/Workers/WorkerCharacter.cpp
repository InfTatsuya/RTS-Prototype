// Fill out your copyright notice in the Description page of Project Settings.


#include "Workers/WorkerCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Preferences/PersonaOptions.h"
#include "Resources/ResourceActor.h"

// Sets default values
AWorkerCharacter::AWorkerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToolMesh"));
	ToolMesh->SetupAttachment(GetMesh(), FName("RightHandSocket"));
	ToolMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceMesh"));
	ResourceMesh->SetupAttachment(GetMesh(), FName("ResourceCarrySocket"));
	ResourceMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AWorkerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorkerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

AResourceActor* AWorkerCharacter::GetNearestResource()
{
	if(!IsValid(ResourceClass)) return nullptr;

	TArray<AActor*> FoundResourceActor;
	UGameplayStatics::GetAllActorsOfClass(this, ResourceClass, FoundResourceActor);

	if(FoundResourceActor.Num() <= 0) return nullptr;
	
	float FoundDistance = 0.f;
	AActor* FoundActor = UGameplayStatics::FindNearestActor(GetActorLocation(), FoundResourceActor, FoundDistance);
	
	return Cast<AResourceActor>(FoundActor);
}

void AWorkerCharacter::ChangeCarryAmount(int32 Amount)
{
	CarryAmount += Amount;
}

ABuildingActor* AWorkerCharacter::GetHome()
{
	return Home;
}

int32 AWorkerCharacter::GetCarryAmount()
{
	return CarryAmount;
}

EResourceType AWorkerCharacter::GetResourceType()
{
	return ResourceType;
}

void AWorkerCharacter::ToggleToolResourceMesh(bool bHoldTool, EResourceType NewResourceType)
{
	if(bHoldTool)
	{
		ToolMesh->SetVisibility(true);
		
		ResourceMesh->SetVisibility(false);
	}
	else
	{
		ToolMesh->SetVisibility(false);
		
		SetCarryingResource(NewResourceType);
		ResourceMesh->SetVisibility(true);
	}
}

void AWorkerCharacter::SetTool(EResourceType NewResourceType)
{
	if(!IsValid(ToolMesh)) return;
	if(!ToolsMap.Contains(NewResourceType)) return;
	if(ToolsMap[NewResourceType] == nullptr) return;
	
	ToolMesh->SetStaticMesh(ToolsMap[NewResourceType]);
}

void AWorkerCharacter::SetCarryingResource(EResourceType NewResourceType)
{
	if(!IsValid(ResourceMesh)) return;
	if(!ResourcesMap.Contains(NewResourceType)) return;
	if(ResourcesMap[NewResourceType] == nullptr) return;
	
	ResourceMesh->SetStaticMesh(ResourcesMap[NewResourceType]);
}

