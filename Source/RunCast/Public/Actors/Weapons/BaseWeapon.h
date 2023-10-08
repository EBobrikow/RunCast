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
#include "BaseWeapon.generated.h"

UCLASS()
class RUNCAST_API ABaseWeapon : public AActor
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float AttackCooldown = 0.2f;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_WeaponFire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void WeaponFire();

	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY()
	bool bCanAttack = true;

	UFUNCTION()
	void CooldownOff();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
