// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ResourcesInterface.h"
#include "ResourceActor.generated.h"

class UTextRenderComponent;
class UCapsuleComponent;

UCLASS()
class RTS_PROTOTYPE_API AResourceActor : public AActor, public IResourcesInterface
{
	GENERATED_BODY()
	
public:	

	AResourceActor();

	//Implements ResourcesInterface
	virtual bool Deplete(int32 DepleteAmount) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY()
	float InitialResourceAmount = 5.0f;

	UPROPERTY()
	float ResourceAmountLeft = 0.f;
};
