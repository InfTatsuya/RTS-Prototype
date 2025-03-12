// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildWidget.generated.h"

class UBuildingBtnWidget;
class UVerticalBox;
class UDataTable;

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UBuildWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveFromParent();

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDataTable> BuildingList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UBuildingBtnWidget> ButtonWidgetClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> Box_Btns;
};
