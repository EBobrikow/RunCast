// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Globals.h"
#include "KillAnnouncerDataContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNCAST_API UKillAnnouncerDataContainer : public UObject
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString KillerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponIconType WeaponIconType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString VicitimName;

	
};
