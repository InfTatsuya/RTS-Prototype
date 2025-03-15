// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingActor.h"
#include "Buildings/BuildingInfo.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/BuildingProgressWidget.h"

ABuildingActor::ABuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeRotation(FRotator(0.f, 30.f, 0.f));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(Root);
	BoxComponent->SetRelativeRotation(FRotator(0.f, 30.f, 0.f));

	BuildProgressBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildProgressBar"));
	BuildProgressBar->SetupAttachment(Root);
}

void ABuildingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(!BuildingName.IsNone())
	{
		DataTableRowHandle.RowName = BuildingName;
	}

	if(IsValid(DataTableRowHandle.DataTable) && !DataTableRowHandle.RowName.IsNone())
	{
		if(F_BuildingInfo* RowInfo = DataTableRowHandle.DataTable->FindRow<F_BuildingInfo>(DataTableRowHandle.RowName, ""))
		{
			StaticMesh->SetStaticMesh(RowInfo->Mesh);
		}
	}

	StaticMesh->SetCollisionProfileName(CollisionProfile.Name);
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlapped);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlapped);
}

void ABuildingActor::SetBuildingMaterial(UMaterialInstance* NewMaterial)
{
	StaticMesh->SetMaterial(0, NewMaterial);
}

void ABuildingActor::SetBuildingMaterial(UMaterialInterface* NewMaterial)
{
	StaticMesh->SetMaterial(0, NewMaterial);
}

void ABuildingActor::StartConstruction()
{
	BuildProgressBar->SetHiddenInGame(false);
	ConstructionProgressValue = 0;
	GetWorldTimerManager().SetTimer(BuildTimerHandle,this, &ThisClass::UpdateBuildProgressBar, 0.1f, true);
}

UMaterialInterface* ABuildingActor::GetBuildingMaterial()
{
	if(StaticMesh)
	{
		return StaticMesh->GetMaterial(0);
	}

	return nullptr;
}

void ABuildingActor::UpdateBuildProgressBar()
{
	ConstructionProgressValue += BuildSpeed;

	if(ProgressWidget == nullptr)
	{
		ProgressWidget = Cast<UBuildingProgressWidget>(BuildProgressBar->GetWidget());
	}
	if(ProgressWidget)
	{
		ProgressWidget->SetProgressBar(ConstructionProgressValue);
	}

	if(ConstructionProgressValue >= 100)
	{
		BuildProgressBar->SetHiddenInGame(true);
		GetWorldTimerManager().ClearTimer(BuildTimerHandle);
	}
}

void ABuildingActor::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                       bool bFromSweep, const FHitResult& SweepResult)
{
	OnBuildingOverlappedDelegate.Broadcast(true);
}

void ABuildingActor::OnEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnBuildingOverlappedDelegate.Broadcast(false);
}

