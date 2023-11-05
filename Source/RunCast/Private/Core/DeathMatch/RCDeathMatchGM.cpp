// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "GameFramework/PlayerStart.h"
#include "Core/DeathMatch/RCDeathMatchPC.h"

void ARCDeathMatchGM::BeginPlay()
{
	Super::BeginPlay();
	SpawnAIControllers();
}

TSubclassOf<APawn> ARCDeathMatchGM::GetDefaultCharacterClass() const
{
	return DefaultCharacterClass;
}

APawn* ARCDeathMatchGM::SpawnCharacter(TSubclassOf<AActor> spawnClass)
{
	APawn* pawn = nullptr;
	//UClass* pawnClass = GetDefaultCharacterClass();

	//ARCDeathMatchPC* DMController = Cast<ARCDeathMatchPC>(controller);
	UClass* pawnClass = spawnClass;//DMController->GetCharacterClass();

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

void ARCDeathMatchGM::SpawnAIControllers()
{
	AIControllers.Empty();
	URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInst)
	{
		TArray<FPlayerData> aiPlayers = gameInst->GetAIPlayersData();
		if (DefaultAIControllerClass)
		{
			for (const FPlayerData& data : aiPlayers)
			{
				FVector loc = FVector::ZeroVector;
				FRotator rot = FRotator::ZeroRotator;
				ARCAIController* aiController = GetWorld()->SpawnActor<ARCAIController>(DefaultAIControllerClass, loc, rot);
				AIControllers.Add(aiController);
				aiController->Init(data);
			}
		}
	}
}
