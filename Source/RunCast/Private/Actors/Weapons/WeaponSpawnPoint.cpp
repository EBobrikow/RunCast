// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/WeaponSpawnPoint.h"

// Sets default values
AWeaponSpawnPoint::AWeaponSpawnPoint()
	: RespawnTime(10.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* defRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defRoot"));
	RootComponent = defRoot;

}

// Called when the game starts or when spawned
void AWeaponSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawmWeaponPickup();
}

void AWeaponSpawnPoint::SpawmWeaponPickup()
{
	if (HasAuthority())
	{
		if (PickupList.Num() > 0)
		{
			int32 randInd = FMath::RandRange(0, PickupList.Num() - 1);
			FVector loc = GetActorLocation() + SpawnOffset;
			FRotator rot = FRotator::ZeroRotator;
		
			CurrentPickup = GetWorld()->SpawnActor<ARCWeaponPickUp>(PickupList[randInd], loc, rot);
			if (CurrentPickup)
			{
				CurrentPickup->OnPickupDelegate.AddDynamic(this, &AWeaponSpawnPoint::Respawn);
			}

		}
	}
	
}

void AWeaponSpawnPoint::Respawn()
{
	if (CurrentPickup)
	{
		//CurrentPickup->ResetOverlap();
		CurrentPickup->OnPickupDelegate.Clear();
		
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AWeaponSpawnPoint::Destroy, 0.2f, false);

		GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);
		GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &AWeaponSpawnPoint::SpawmWeaponPickup, RespawnTime, false);
	}
}

void AWeaponSpawnPoint::Destroy()
{
	if (CurrentPickup)
	{
		CurrentPickup->Destroy();
	}
}

// Called every frame
void AWeaponSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

