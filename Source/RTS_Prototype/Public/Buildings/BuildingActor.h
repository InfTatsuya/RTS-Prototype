// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.generated.h"

class UWidgetComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingOverlapped, bool);

class UBoxComponent;
class UMaterialInterface;
class UBuildingProgressWidget;

UCLASS()
class RTS_PROTOTYPE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABuildingActor();
	virtual void OnConstruction(const FTransform& Transform) override;
	void SetBuildingMaterial(UMaterialInstance* NewMaterial);
	void SetBuildingMaterial(UMaterialInterface* NewMaterial);

	void StartConstruction();

	UMaterialInterface* GetBuildingMaterial();

	UPROPERTY()
	FName BuildingName;

	FOnBuildingOverlapped OnBuildingOverlappedDelegate;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UWidgetComponent> BuildProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataTableRowHandle DataTableRowHandle;

	FTimerHandle BuildTimerHandle;

	void UpdateBuildProgressBar();

	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FCollisionProfileName CollisionProfile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int BuildSpeed = 1;

	int32 ConstructionProgressValue = 0;

	UPROPERTY()
	UBuildingProgressWidget* ProgressWidget = nullptr;

};
