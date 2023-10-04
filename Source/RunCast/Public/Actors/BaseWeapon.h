// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Actors/RCWeaponPickUp.h"
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

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<ARCWeaponPickUp> WeaponPickClass;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
