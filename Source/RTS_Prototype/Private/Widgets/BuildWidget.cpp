// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildWidget.h"
#include "Components/VerticalBox.h"
#include "Library/CommonLibraryFunction.h"
#include "Pawns/RTS_PlayerController.h"
#include "Widgets/BuildingBtnWidget.h"

void UBuildWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(IsValid(BuildingList) && IsValid(ButtonWidgetClass))
	{
		TArray<FName> RowNameArray = BuildingList->GetRowNames();
		for(const FName& RowName : RowNameArray)
		{
			UBuildingBtnWidget* NewBtn = CreateWidget<UBuildingBtnWidget>(this, ButtonWidgetClass);
			if(F_BuildingInfo* Item = BuildingList->FindRow<F_BuildingInfo>(RowName, ""))
			{
				F_BuildingInfo CurrentItem = *Item;
				NewBtn->SetBtnData(CurrentItem);
				NewBtn->SetBtnBuildingName(RowName);
				NewBtn->OnClicked.AddUObject(this, &ThisClass::OnBuildingBtnClicked);
				Box_Btns->AddChildToVerticalBox(NewBtn);
			}
		}
	}
}

void UBuildWidget::OnBuildingBtnClicked(FName BuildingName)
{
	ARTS_PlayerController* PlayerController = UCommonLibraryFunction::GetMyController(this);
	PlayerController->EnterPlacementMode(BuildingName);

	PlayerController->ClearBuildWidget();
	OnRemoveFromParent();
}
