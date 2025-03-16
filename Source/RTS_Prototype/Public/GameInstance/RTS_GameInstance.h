// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Resources/ResourcesEnum.h"
#include "RTS_GameInstance.generated.h"

class UDataTable;

typedef TMap<EResourceType, int> FMyMap; 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAlterResources, FMyMap)

/**
 * 
 */
UCLASS()
class RTS_PROTOTYPE_API URTS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	URTS_GameInstance();

	bool CheckResource(EResourceType ResourceType, int32 Required);
	void AlterResource(EResourceType ResourceType, int32 Amount);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Data")
	TMap<EResourceType, int> Resources;

	TMap<EResourceType, int> GetResources();

	TMap<EResourceType, int> GetResourcesForBuilding(const FName& BuildingName) const;
	void UpdateResourceByBuilding(const FName& BuildingName);

	FOnAlterResources OnAlterResourcesDelegate;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table Data", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> BuildingDataList;
	
};
