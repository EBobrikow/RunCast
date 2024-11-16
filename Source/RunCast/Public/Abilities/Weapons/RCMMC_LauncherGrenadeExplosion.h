// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "RCMMC_LauncherGrenadeExplosion.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCMMC_LauncherGrenadeExplosion : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	URCMMC_LauncherGrenadeExplosion();


	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};