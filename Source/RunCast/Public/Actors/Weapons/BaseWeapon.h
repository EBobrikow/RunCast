// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Library/ALSCharacterEnumLibrary.h"
#include "Actors/Projectiles/BaseProjectile.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"
#include "Abilities/RCGameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "Components/RCAbilitySystemComponent.h"
#include "BaseWeapon.generated.h"

UCLASS()
class RUNCAST_API ABaseWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponSkeletalMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	EALSOverlayState WeaponOverlayState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* FireMontage;


	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_WeaponFire(bool val);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayMontage(UAnimMontage* montage);

	UPROPERTY()
	ACharacter* OwnerCharacter = nullptr;

	UFUNCTION()
	void SetTargetLocation(FVector loc);

	virtual void WeaponFire(bool val);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void FireAction();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bCanAttack = false;

	UFUNCTION()
	void AbilityTickFire();

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URCAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TSubclassOf<URCGameplayAbility> PrimaryAbility;

	UPROPERTY()
	bool AbilityInitialized = false;

	void AddStartupGameplayAbilities();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
