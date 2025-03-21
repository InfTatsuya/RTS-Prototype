#pragma once

UENUM(BlueprintType)
enum class EWorkerState : uint8
{
	EWS_Idle UMETA(DisplayName = "Idle"),
	EWS_Walking UMETA(DisplayName = "Walking"),
	EWS_Collecting UMETA(DisplayName = "Collecting"),
	EWS_Returning UMETA(DisplayName = "Returning"),

	EWS_MAX UMETA(DisplayName = "Default MAX")
};
