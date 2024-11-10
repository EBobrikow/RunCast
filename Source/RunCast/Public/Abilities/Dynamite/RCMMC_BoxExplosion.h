// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "RCMMC_BoxExplosion.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCMMC_BoxExplosion : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public: 

	URCMMC_BoxExplosion();


	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition HealthDef;

private: 

	float ExplosionRadius = 800.0f;

	float ExplosionDamage = 150.0f;
	
};
