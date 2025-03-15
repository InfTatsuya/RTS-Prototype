// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/RTS_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Buildings/SpawnerActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pawns/CameraPawn.h"
#include "Widgets/BuildWidget.h"

void ARTS_PlayerController::EnterPlacementMode(const FName& BuildingName)
{
	if(SpawnerActorClass == nullptr) return;

	CurrentSpawnerActor = GetWorld()->SpawnActorDeferred<ASpawnerActor>(SpawnerActorClass, FTransform::Identity);
	CurrentSpawnerActor->RequestedBuildingName = BuildingName;
	CurrentSpawnerActor->FinishSpawning(FTransform::Identity);
}

void ARTS_PlayerController::ClearBuildWidget()
{
	BuildWidget = nullptr;
}

void ARTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(!PlayerPawn)
	{
		PlayerPawn = Cast<ACameraPawn>(GetPawn());
	}

	SetShowMouseCursor(true);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if(Subsystem && RTSMappingContext)
	{
		Subsystem->AddMappingContext(RTSMappingContext, 0);
	}

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetPawn()->InputComponent))
	{
		check(MoveVerticalInputAction);
		EnhancedInputComponent->BindAction(MoveVerticalInputAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::MoveVertical);

		check(MoveHorizontalInputAction);
		EnhancedInputComponent->BindAction(MoveHorizontalInputAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::MoveHorizontal);

		check(CameraZoomInputAction);
		EnhancedInputComponent->BindAction(CameraZoomInputAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::CameraZoom);

		check(BuildInputAction);
		EnhancedInputComponent->BindAction(BuildInputAction, ETriggerEvent::Started, this, &ARTS_PlayerController::ToggleBuildWidget);

		check(ClickedAction);
		EnhancedInputComponent->BindAction(ClickedAction, ETriggerEvent::Started, this, &ARTS_PlayerController::PlaceBuildingAction);
	}
}

void ARTS_PlayerController::MoveVertical(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	FVector ForwardVector = GetPawn()->GetActorForwardVector();
	ForwardVector.Z = 0.f;
	FVector Offset = MovementSpeed * FloatValue * ForwardVector;
	GetPawn()->AddActorWorldOffset(Offset);
}

void ARTS_PlayerController::MoveHorizontal(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	FVector RightVector = GetPawn()->GetActorRightVector();
	RightVector.Z = 0.f;
	FVector Offset = MovementSpeed * FloatValue * RightVector;
	GetPawn()->AddActorWorldOffset(Offset);
}

void ARTS_PlayerController::CameraZoom(const FInputActionValue& Value)
{
	if(!PlayerPawn)
	{
		PlayerPawn = Cast<ACameraPawn>(GetPawn());
	}

	check(PlayerPawn);
	if(USpringArmComponent* SpringArmComponent = PlayerPawn->GetCameraBoom())
	{
		const float FloatValue = Value.Get<float>();
		float NewTargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + FloatValue * CameraZoomSpeed, 50.f, 1000.f);
		SpringArmComponent->TargetArmLength = NewTargetArmLength;
	}
}

void ARTS_PlayerController::ToggleBuildWidget(const FInputActionValue& Value)
{
	if(IsValid(BuildWidget))
	{
		BuildWidget->OnRemoveFromParent();
		BuildWidget = nullptr;
	}
	else
	{
		if(!IsValid(BuildWidgetClass)) return;

		BuildWidget = CreateWidget<UBuildWidget>(this, BuildWidgetClass);
		BuildWidget->AddToViewport();
	}
}

void ARTS_PlayerController::PlaceBuildingAction(const FInputActionValue& Value)
{
	if(!IsValid(CurrentSpawnerActor)) return;
	if(CurrentSpawnerActor->IsOverlapping()) return;

	CurrentSpawnerActor->OnReleasedBuidling();
	CurrentSpawnerActor->Destroy();
	CurrentSpawnerActor = nullptr;
}
