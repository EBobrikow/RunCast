// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "Net/UnrealNetwork.h"
#include "RCWeaponPickUp.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickup);

UCLASS()
class RUNCAST_API ARCWeaponPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARCWeaponPickUp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USphereComponent* BaseSphere = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY();
	FOnPickup OnPickupDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	FTimerHandle PickUpResetTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ResetTime = 15.0f;

	UFUNCTION()
	void ResetSpawn();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_DrawSphere();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
