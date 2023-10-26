// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "Actors/NetSpawnPoint.h"
#include "Characters/RCCharacter.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"

void ARCDeathMatchPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		Server_CreateCharacter();
	}
	//CreateCharacter();
}

void ARCDeathMatchPC::CreateCharacter()
{
	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			ARCCharacter* character = Cast<ARCCharacter>(GM->SpawnCharacter(this));
			if (character)
			{
				Possess(character);
				auto hp = character->GetHealthComponent();
				if (hp)
				{
					hp->OnActorKilled.AddDynamic(this, &ARCDeathMatchPC::CharacterKilled);
					hp->OnHealthUpdate.AddDynamic(this, &ARCDeathMatchPC::HealthUpdate);
					//HealthUpdate(hp->GetMaxHealth());
					HealthUpdate(hp->GetCurrentHealth());
				}
			}
			
		}
	}
}

void ARCDeathMatchPC::Server_CreateCharacter_Implementation()
{
	CreateCharacter();
}

void ARCDeathMatchPC::CharacterKilled()
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		auto hp = character->GetHealthComponent();
		if (hp)
		{
			hp->OnActorKilled.Clear();
			hp->OnHealthUpdate.Clear();
		}

		character->RagdollAction();
		character->DisableInput(this);
		//character->EnableInput(this);
		GetWorld()->GetTimerManager().ClearTimer(RestartDelay);
		GetWorld()->GetTimerManager().SetTimer(RestartDelay, this, &ARCDeathMatchPC::Restart, RestartDelayTime, false);
	}
	
}

void ARCDeathMatchPC::HealthUpdate(float val)
{
	Client_UpdateHealthStatus(val);
}

void ARCDeathMatchPC::Client_UpdateHealthStatus_Implementation(const float hp)
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->UpdateHealthBar(hp);
	}
}

void ARCDeathMatchPC::Restart()
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		UnPossess();
		character->Destroy();
		CreateCharacter();
		
		/*UHealthComponent* hpComp = character->GetHealthComponent();
		if (hpComp)
		{
			Client_UpdateHealthStatus(hpComp->GetCurrentHealth());
		}*/
		
		//Client_UpdateHealthStatus(hud->GetCharacterHP());
		//hud->UpdateHealthBar(hud->GetCharacterHP());
		
	}
}
