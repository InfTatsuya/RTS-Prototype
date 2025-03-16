// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	ERT_Wood UMETA(DisplayName = "Wood"),
	ERT_Rock UMETA(DisplayName = "Rock"),
	ERT_Money UMETA(DisplayName = "Money"),

	ERT_MAX UMETA(DisplayName = "Default MAX")
};
