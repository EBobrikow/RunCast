// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "Characters/RCCharacter.h"

ARCAIController::ARCAIController()
{
}

void ARCAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ARCAIController::Init(FPlayerData playerData)
{
	PlayerData = playerData;
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
				auto hp = character->GetHealthComponent();
				if (hp)
				{
					hp->OnActorKilled.AddDynamic(this, &ARCAIController::CharacterKilled);
				}
			}

		}
	}
}

void ARCAIController::CharacterKilled()
{
	ARCCharacter* character = Cast<ARCCharacter>(GetPawn());
	if (character)
	{
		character->KillCharacter();
		BrainComponent->StopLogic("Dead");


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