// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "Interfaces/DamagebleInterface.h"
#include "RCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCCharacter : public AALSCharacter, public IDamagebleInterface
{
	GENERATED_BODY()

public: 

	ARCCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LightAttackAction(bool val);

	UFUNCTION(BlueprintCallable)
	void SetAttackAlpha(float alpha);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;

	virtual void ApplyDamage(float dmg) override;
protected: 

	
};
