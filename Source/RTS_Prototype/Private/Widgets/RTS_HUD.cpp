// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/RTS_HUD.h"

#include "Library/CommonLibraryFunction.h"
#include "Pawns/RTS_PlayerController.h"
#include "Widgets/ResourceHUD.h"

void ARTS_HUD::BeginPlay()
{
	Super::BeginPlay();

	if(ResourceHUDClass)
	{
		ARTS_PlayerController* PlayerController = UCommonLibraryFunction::GetMyController(this);
		
		ResourceHUDWidget = CreateWidget<UResourceHUD>(PlayerController, ResourceHUDClass);
		ResourceHUDWidget->AddToViewport();
	}
}
