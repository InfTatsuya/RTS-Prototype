// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceActor.h"

#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"


AResourceActor::AResourceActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
	StaticMesh->SetRelativeScale3D(FVector(0.3f));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleComponent->SetupAttachment(Root);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRenderComponent->SetupAttachment(Root);
}

bool AResourceActor::Deplete(int32 DepleteAmount)
{
	ResourceAmountLeft -= DepleteAmount;
	if(ResourceAmountLeft <= 0.f)
	{
		Destroy();
		return true;
	}
	else
	{
		return false;
	}
	
}

void AResourceActor::BeginPlay()
{
	Super::BeginPlay();

	ResourceAmountLeft = InitialResourceAmount;
}


