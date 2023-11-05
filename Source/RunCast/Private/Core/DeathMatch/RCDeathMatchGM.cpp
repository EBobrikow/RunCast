// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "GameFramework/PlayerStart.h"
#include "Core/DeathMatch/RCDeathMatchPC.h"

void ARCDeathMatchGM::BeginPlay()
{
	Super::BeginPlay();
}

TSubclassOf<APawn> ARCDeathMatchGM::GetDefaultCharacterClass() const
{
	return DefaultCharacterClass;
}

APawn* ARCDeathMatchGM::SpawnCharacter(APlayerController* controller)
{
	APawn* pawn = nullptr;
	//UClass* pawnClass = GetDefaultCharacterClass();

	ARCDeathMatchPC* DMController = Cast<ARCDeathMatchPC>(controller);
	UClass* pawnClass = DMController->GetCharacterClass();

#if WITH_EDITOR
	//pawnClass = GetDefaultCharacterClass();
#endif
	 
	if (pawnClass)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			int32 randInd = FMath::RandRange(0, FoundActors.Num()-1);
			FVector loc = FoundActors[randInd]->GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Spawn location: %f, %f, %f"), loc.X, loc.Y, loc.Z);
			FRotator rot = FRotator::ZeroRotator;
			pawn = GetWorld()->SpawnActor<APawn>(pawnClass, loc, rot);
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ARCDeathMatchPC::CreateCharacter No spawn points was found"));
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ARCDeathMatchPC::CreateCharacter Invalid pawn class to spawn"));
	}
	return pawn;
}
