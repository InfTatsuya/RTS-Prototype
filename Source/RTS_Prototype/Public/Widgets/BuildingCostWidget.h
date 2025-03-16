// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingCostWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UBuildingCostWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetBuildingCost(const FString& ResourceName, int32 ResourceValue) const;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCostWidgetVisual();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "BuildingCost")
	bool bAffordableCost = true;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Resource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_Cost;
	
};
