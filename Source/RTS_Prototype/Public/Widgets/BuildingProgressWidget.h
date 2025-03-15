// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingProgressWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UBuildingProgressWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetProgressBar(int32 NewValue);
	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBarRef;
};
