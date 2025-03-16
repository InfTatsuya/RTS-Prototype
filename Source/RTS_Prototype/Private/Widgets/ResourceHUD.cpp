// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ResourceHUD.h"

#include "Components/TextBlock.h"
#include "GameInstance/RTS_GameInstance.h"
#include "Library/CommonLibraryFunction.h"
#include "Resources/ResourcesEnum.h"

void UResourceHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if(URTS_GameInstance* MyGameInstance = UCommonLibraryFunction::GetGameInstance(this))
	{
		MyGameInstance->OnAlterResourcesDelegate.AddUObject(this, & ThisClass::OnUpdateResources);
		
		auto Resources = MyGameInstance->GetResources();
		OnUpdateResources(Resources);
	}
}

void UResourceHUD::OnUpdateResources(TMap<EResourceType, int32> Resources)
{
	for(const auto& Resource : Resources)
	{
		switch(Resource.Key)
		{
		case EResourceType::ERT_Wood:
			Txt_Wood->SetText(FText::FromString(FString::FromInt(Resource.Value)));
			break;
				
		case EResourceType::ERT_Rock:
			Txt_Rock->SetText(FText::FromString(FString::FromInt(Resource.Value)));
			break;
				
		case EResourceType::ERT_Money:
			break;
				
		default:
			break;
		}
	}
}
