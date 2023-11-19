// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Weapons/RCWeaponPickUp.h"
#include "Net/UnrealNetwork.h"
#include "WeaponSpawnPoint.generated.h"

UCLASS()
class RUNCAST_API AWeaponSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponSpawnPoint();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<ARCWeaponPickUp>> PickupList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RespawnTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector SpawnOffset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FTimerHandle RespawnTimer;

	UPROPERTY()
	FTimerHandle DestroyTimer;

	UFUNCTION()
	void SpawmWeaponPickup();

	UFUNCTION()
	void Respawn();

	UFUNCTION()
	void Destroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private: 

	ARCWeaponPickUp* CurrentPickup = nullptr;
};
