// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingBtnWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBuildingBtnWidget::SetBtnData(const F_BuildingInfo& BuildingData)
{
	BtnBuildingData = BuildingData;

	SetBuildingName(BuildingData.Name);
	SetBuildingIcon(BuildingData.Icon);
}

void UBuildingBtnWidget::SetBuildingName(const FText& TextName) const
{
	Text_Name->SetText(TextName);
}

void UBuildingBtnWidget::SetBuildingIcon(UTexture2D* IconTexture) const
{
	Img_Icon->SetBrushFromTexture(IconTexture, true);
}
