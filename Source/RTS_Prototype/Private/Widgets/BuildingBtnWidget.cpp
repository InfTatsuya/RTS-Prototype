// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingBtnWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameInstance/RTS_GameInstance.h"
#include "Library/CommonLibraryFunction.h"
#include "Widgets/BuildingCostWidget.h"
#include "Resources/ResourcesEnum.h"

void UBuildingBtnWidget::SetBtnData(const F_BuildingInfo& BuildingData)
{
	BtnBuildingData = BuildingData;

	SetBuildingName(BuildingData.Name);
	SetBuildingIcon(BuildingData.Icon);
	SetBuildingCost();

	Btn_Building->OnClicked.AddDynamic(this, &ThisClass::OnBuildingBtnClick);
}

void UBuildingBtnWidget::SetBtnBuildingName(const FName& Name)
{
	BuildingName = Name;
}

void UBuildingBtnWidget::SetBuildingName(const FText& TextName) const
{
	Text_Name->SetText(TextName);
}

void UBuildingBtnWidget::SetBuildingIcon(UTexture2D* IconTexture) const
{
	Img_Icon->SetBrushFromTexture(IconTexture, true);
}

void UBuildingBtnWidget::SetBuildingCost()
{
	if(!IsValid(CostWidgetClass)) return;

	URTS_GameInstance* GameInstance = UCommonLibraryFunction::GetGameInstance(this);
	if(!GameInstance) return;
	
	for(const TTuple<EResourceType, int>& Cost : BtnBuildingData.Cost)
	{
		UBuildingCostWidget* NewCostWidget = CreateWidget<UBuildingCostWidget>(this, CostWidgetClass);
		NewCostWidget->SetBuildingCost(UCommonLibraryFunction::GetResourceName(Cost.Key), Cost.Value);

		UPanelSlot* NewSlot = Box_Cost->AddChild(NewCostWidget);
		UHorizontalBoxSlot* HSlot = Cast<UHorizontalBoxSlot>(NewSlot);
		HSlot->SetSize(ESlateSizeRule::Fill);

		bool CheckResource = GameInstance->CheckResource(Cost.Key, Cost.Value);
		NewCostWidget->bAffordableCost = CheckResource;
		NewCostWidget->UpdateCostWidgetVisual();
		
		if(!CheckResource)
		{
			bHasEnoughResource = false;
		}
	}
}

void UBuildingBtnWidget::OnBuildingBtnClick()
{
	if(!bHasEnoughResource) return;
	
	OnClicked.Broadcast(BuildingName);
}
