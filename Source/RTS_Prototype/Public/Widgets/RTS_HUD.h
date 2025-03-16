// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

class UResourceHUD;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UResourceHUD> ResourceHUDClass;

	UPROPERTY()
	TObjectPtr<UResourceHUD> ResourceHUDWidget;
	
};
