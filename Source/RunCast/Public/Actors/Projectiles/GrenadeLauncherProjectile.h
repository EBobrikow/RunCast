// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Projectiles/BaseProjectile.h"
#include "GrenadeLauncherProjectile.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API AGrenadeLauncherProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExplosionRadius = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExplosionDamage = 70.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> GrenadeExplosionEffect;

protected: 

	UFUNCTION(BlueprintCallable)
	void ApplyExplosionDamage();

	virtual void PostHit() override;
	
};
