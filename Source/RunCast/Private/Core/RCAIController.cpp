// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "Characters/RCCharacter.h"
#include "Core/RCGameState.h"

ARCAIController::ARCAIController()
{
}

void ARCAIController::BeginPlay()
{
	Super::BeginPlay();

	ScoreData = FScoreBoardData();

	ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{

		GM->OnMatchEnd.AddDynamic(this, &ARCAIController::MatchEnd);
	}
}

void ARCAIController::Init(FPlayerData playerData)
{
	PlayerData = playerData;
	ScoreData.PlayerName = PlayerData.PlayerName;
	ARCGameState* gameState = GetWorld()->GetGameState<ARCGameState>();
	if (gameState)
	{
		gameState->Server_UpdateScoreBoard();
	}
	CreateCharacter();
}

void ARCAIController::CreateCharacter()
{
	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM && PlayerData.SelectedCharacterClass)
		{
			ARCCharacter* character = Cast<ARCCharacter>(GM->SpawnCharacter(PlayerData.SelectedCharacterClass));
			if (character)
			{
				Possess(character);
				auto Attrib = character->GetAttributes();
				if (Attrib)
				{
					Attrib->OnCharacterKilled.AddDynamic(this, &ARCAIController::CharacterKilled);
				}
				
			}

		}
	}
}

void ARCAIController::CharacterKilled(AActor* killer)
{
	ARCCharacter* character = Cast<ARCCharacter>(GetPawn());
	if (character)
	{
		character->KillCharacter();
		BrainComponent->StopLogic("Dead");

		if (killer)
		{
			if (ACharacter* killerChar = Cast<ACharacter>(killer))
			{
				IScoreBoardInterface* scoreBoardInterface = Cast<IScoreBoardInterface>(killerChar->GetController());
				if (scoreBoardInterface)
				{
					scoreBoardInterface->AddKillCount();
				}
			}
			
		}

		AddDeathCount();

		ARCGameState* gameState = GetWorld()->GetGameState<ARCGameState>();
		if (gameState)
		{
			gameState->Server_UpdateScoreBoard();
			gameState->Server_AnounceCharacterKilled(killer, character);
		}

		GetWorld()->GetTimerManager().ClearTimer(RestartDelay);
		GetWorld()->GetTimerManager().SetTimer(RestartDelay, this, &ARCAIController::Restart, RestartDelayTime, false);
	}
}



void ARCAIController::Restart()
{
	ARCCharacter* character = Cast<ARCCharacter>(GetPawn());
	if (character)
	{
		UnPossess();
		character->Destroy();
		CreateCharacter();

	}
}

void ARCAIController::MatchEnd()
{
	BrainComponent->StopLogic("GameEnd");
}

void ARCAIController::AddKillCount()
{
	ScoreData.KillCount += 1;
}

void ARCAIController::AddDeathCount()
{
	ScoreData.DeathCount += 1;
}

FScoreBoardData ARCAIController::GetScoreBoardData()
{
	return ScoreData;
}
