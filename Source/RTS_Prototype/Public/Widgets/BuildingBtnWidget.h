// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Building/BuildingInfo.h"
#include "BuildingBtnWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;
/**
 * 
 */
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

	void SetBtnData(const F_BuildingInfo& BuildingData);

protected:
	
	void SetBuildingName(const FText& TextName) const;
	void SetBuildingIcon(UTexture2D* IconTexture) const;

	UPROPERTY()
	F_BuildingInfo BtnBuildingData = F_BuildingInfo();
};
