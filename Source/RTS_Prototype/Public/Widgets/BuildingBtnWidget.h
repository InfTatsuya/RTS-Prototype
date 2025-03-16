// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Buildings/BuildingInfo.h"
#include "BuildingBtnWidget.generated.h"

class UBuildingCostWidget;
class UHorizontalBox;
class UTextBlock;
class UImage;
class UButton;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingBtnClicked, FName);

UCLASS()
class RTS_PROTOTYPE_API UBuildingBtnWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Building;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Img_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Name;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> Box_Cost;

	void SetBtnData(const F_BuildingInfo& BuildingData);
	void SetBtnBuildingName(const FName& Name);
	
	FOnBuildingBtnClicked OnClicked;

protected:
	
	void SetBuildingName(const FText& TextName) const;
	void SetBuildingIcon(UTexture2D* IconTexture) const;
	void SetBuildingCost();

	UPROPERTY()
	F_BuildingInfo BtnBuildingData = F_BuildingInfo();

	UPROPERTY()
	FName BuildingName;

	UFUNCTION()
	void OnBuildingBtnClick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Class Ref")
	TSubclassOf<UBuildingCostWidget> CostWidgetClass;

private:

	UPROPERTY()
	bool bHasEnoughResource = true;
};
