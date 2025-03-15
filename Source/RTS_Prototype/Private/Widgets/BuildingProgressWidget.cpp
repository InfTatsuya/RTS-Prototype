// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingProgressWidget.h"
#include "Components/ProgressBar.h"

void UBuildingProgressWidget::SetProgressBar(int32 NewValue)
{
	float ProgressValue = FMath::Clamp(NewValue / 100.f, 0.f, 100.f);
	ProgressBarRef->SetPercent(ProgressValue);
}
