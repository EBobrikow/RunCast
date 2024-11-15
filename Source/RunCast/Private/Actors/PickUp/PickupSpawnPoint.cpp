// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUp/PickupSpawnPoint.h"

// Sets default values
APickupSpawnPoint::APickupSpawnPoint()
	: RespawnTime(10.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* defRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defRoot"));
	RootComponent = defRoot;

}

// Called when the game starts or when spawned
void APickupSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawmWeaponPickup();
}

void APickupSpawnPoint::SpawmWeaponPickup()
{
	if (HasAuthority())
	{
		if (PickupList.Num() > 0)
		{
			int32 randInd = FMath::RandRange(0, PickupList.Num() - 1);
			FVector loc = GetActorLocation() + SpawnOffset;
			FRotator rot = FRotator::ZeroRotator;
		
			CurrentPickup = GetWorld()->SpawnActor<ARCBasePickUp>(PickupList[randInd], loc, rot);
			if (CurrentPickup)
			{
				CurrentPickup->OnPickupDelegate.AddDynamic(this, &APickupSpawnPoint::Respawn);
			}

		}
	}
	
}

void APickupSpawnPoint::Respawn()
{
	if (CurrentPickup)
	{
		//CurrentPickup->ResetOverlap();
		CurrentPickup->OnPickupDelegate.Clear();
		
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &APickupSpawnPoint::Destroy, 0.2f, false);

		GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);
		GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &APickupSpawnPoint::SpawmWeaponPickup, RespawnTime, false);
	}
}

void APickupSpawnPoint::Destroy()
{
	if (CurrentPickup)
	{
		CurrentPickup->Destroy();
	}
}

// Called every frame
void APickupSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

