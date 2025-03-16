// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Resources/ResourcesEnum.h"
#include "ResourceHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API UResourceHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Wood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Rock;

	void OnUpdateResources(TMap<EResourceType, int32> Resources);
};
