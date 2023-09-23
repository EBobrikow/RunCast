// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NetSpawnPoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ANetSpawnPoint::ANetSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

// Called when the game starts or when spawned
void ANetSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	/*FVector origin, boxExtent;
	float radius = 0.0f;
	UKismetSystemLibrary::GetComponentBounds(BaseSphereCollision, origin, boxExtent, radius);
	if (UKismetMathLibrary::IsPointInBox(player->GetActorLocation(), origin, boxExtent))
	{
		CallSaveGame();
	}*/
	
}

// Called every frame
void ANetSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

