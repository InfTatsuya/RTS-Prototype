// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RTS_GameInstance.h"

#include "Buildings/BuildingInfo.h"

URTS_GameInstance::URTS_GameInstance()
{
	Resources.Add(EResourceType::ERT_Wood, 5);
	Resources.Add(EResourceType::ERT_Rock, 10);
}

bool URTS_GameInstance::CheckResource(EResourceType ResourceType, int32 Required)
{
	if(!Resources.Contains(ResourceType)) return false;
	if(Resources[ResourceType] < Required) return false;

	return true;
}

void URTS_GameInstance::AlterResource(EResourceType ResourceType, int32 Amount)
{
	if(!Resources.Contains(ResourceType)) return;

	Resources[ResourceType] += Amount;

	OnAlterResourcesDelegate.Broadcast(Resources);
}

TMap<EResourceType, int> URTS_GameInstance::GetResources()
{
	return Resources;
}

TMap<EResourceType, int> URTS_GameInstance::GetResourcesForBuilding(const FName& BuildingName) const
{
	F_BuildingInfo* BuildingInfo = BuildingDataList->FindRow<F_BuildingInfo>(BuildingName, "");
	if(!BuildingInfo) return TMap<EResourceType, int>();
	
	return  BuildingInfo->Cost;
}

void URTS_GameInstance::UpdateResourceByBuilding(const FName& BuildingName)
{
	TMap<EResourceType, int> Cost = GetResourcesForBuilding(BuildingName);
	for(const auto& Item : Cost)
	{
		AlterResource(Item.Key, -Item.Value);

		//UE_LOG(LogTemp, Warning, TEXT("New Resource %s : %d"), *UEnum::GetValueAsString(Item.Key), Resources[Item.Key]);
	}
}
