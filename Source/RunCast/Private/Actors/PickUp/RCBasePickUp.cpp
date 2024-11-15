// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUp/RCBasePickUp.h"

// Sets default values
ARCBasePickUp::ARCBasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FOnPickup ARCBasePickUp::GetPickupDelegate()
{
	return OnPickupDelegate;
}

// Called when the game starts or when spawned
void ARCBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

