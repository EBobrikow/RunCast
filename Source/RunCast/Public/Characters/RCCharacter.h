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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ABaseWeapon* HoldWeaponRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION(Server, Reliable)
	void Server_LightAttackAction(const bool val);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetAnimState(EALSOverlayState overlay);

	UFUNCTION(Server, Reliable)
	void Server_SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void ApplyDamageBP(float dmg, ACharacter* damager);

	UFUNCTION(BlueprintCallable)
	void KillCharacter();

	virtual void ApplyDamage(float dmg, ACharacter* damager) override;

	UHealthComponent* GetHealthComponent() const;

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* ChildActorComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> CurrentWeaponClass;

	UPROPERTY()
	FTimerHandle DefWeaponSpawnDelay;

	UFUNCTION()
	void SpawnDefaultWeapon();

	virtual void AttackActionBase(bool val) override;
};
