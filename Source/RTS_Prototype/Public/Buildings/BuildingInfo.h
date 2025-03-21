#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourcesEnum.h"
#include "BuildingInfo.generated.h"

class AResourceActor;

USTRUCT(BlueprintType)
struct F_BuildingInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceType ResourceType = EResourceType::ERT_MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AResourceActor> ResourceClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EResourceType, int32> Cost;
	
};

