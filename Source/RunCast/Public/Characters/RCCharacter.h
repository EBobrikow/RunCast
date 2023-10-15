// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "Interfaces/DamagebleInterface.h"
#include "Components/HealthComponent.h"
#include "Components/ChildActorComponent.h"
#include "Net/UnrealNetwork.h"
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
	
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION(Server, Reliable)
	void Server_LightAttackAction(const bool val);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetAnimState(EALSOverlayState overlay);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ABaseWeapon* HoldWeaponRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;

	UFUNCTION(Server, Reliable)
	void Server_SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	virtual void ApplyDamage(float dmg) override;
protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* ChildActorComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> CurrentWeaponClass;

	virtual void AttackActionBase(bool val) override;
};
