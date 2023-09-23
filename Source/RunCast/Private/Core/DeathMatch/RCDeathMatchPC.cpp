// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "Actors/NetSpawnPoint.h"

void ARCDeathMatchPC::BeginPlay()
{
	Super::BeginPlay();

	CreateCharacter();
}

void ARCDeathMatchPC::CreateCharacter()
{
	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			UClass* pawnClass = GM->GetDefaultPawnClassForController(this);
			if (pawnClass)
			{
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANetSpawnPoint::StaticClass(), FoundActors);
				if (FoundActors.Num() > 0)
				{
					int32 randInd = FMath::RandRange(0, FoundActors.Num()-1);
					FVector loc = FoundActors[randInd]->GetActorLocation();
					UE_LOG(LogTemp, Warning, TEXT("Spawn location: %f, %f, %f"), loc.X, loc.Y, loc.Z);
					FRotator rot = FRotator::ZeroRotator;
					APawn* pawn = GetWorld()->SpawnActor<APawn>(pawnClass, loc, rot);
					if (pawn)
					{
						Possess(pawn);
					}
				}

				
			}
		}
	}
}
