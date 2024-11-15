// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Interfaces/SpawnPointInterface.h"
#include "RCBasePickUp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickup);

UCLASS()
class RUNCAST_API ARCBasePickUp : public AActor //, public ISpawnPointInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARCBasePickUp();

	virtual FOnPickup GetPickupDelegate();

	UPROPERTY();
	FOnPickup OnPickupDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
