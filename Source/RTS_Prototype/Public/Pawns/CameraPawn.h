// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RTS_PROTOTYPE_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	
	ACameraPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	
public:

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	

};
