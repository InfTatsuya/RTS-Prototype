// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingCostWidget.h"
#include "Components/TextBlock.h"

void UBuildingCostWidget::SetBuildingCost(const FString& ResourceName, int32 ResourceValue) const
{
	Text_Resource->SetText(FText::FromString(ResourceName));
	Text_Cost->SetText(FText::FromString(FString::FromInt(ResourceValue)));
}
