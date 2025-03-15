// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PlayerController.generated.h"

class ASpawnerActor;
class UBuildWidget;
class ACameraPawn;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void EnterPlacementMode(const FName& BuildingName);
	void ClearBuildWidget();

protected:

	virtual void BeginPlay() override;

	void MoveVertical(const FInputActionValue& Value);
	void MoveHorizontal(const FInputActionValue& Value);
	void CameraZoom(const FInputActionValue& Value);
	void ToggleBuildWidget(const FInputActionValue& Value);
	void PlaceBuildingAction(const FInputActionValue& Value);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> RTSMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> MoveVerticalInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> MoveHorizontalInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> CameraZoomInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> BuildInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> ClickedAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configure Inputs")
	float MovementSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configure Inputs")
	float CameraZoomSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UBuildWidget> BuildWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UBuildWidget> BuildWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building Actor")
	TSubclassOf<ASpawnerActor> SpawnerActorClass;

private:

	UPROPERTY()
	TObjectPtr<ACameraPawn> PlayerPawn;

	UPROPERTY()
	TObjectPtr<ASpawnerActor> CurrentSpawnerActor;
};
