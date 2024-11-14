// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Abilities/RCAttributeSet.h"

void ARCDeathMatchPC::BeginPlay()
{
	Super::BeginPlay();

	ScoreData = FScoreBoardData();

	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->OnMatchBegin.AddDynamic(this, &ARCDeathMatchPC::Client_Init);
			GM->OnMatchEnd.AddDynamic(this, &ARCDeathMatchPC::MatchEnd);
		}

		ARCGameState* gameState = GetWorld()->GetGameState<ARCGameState>();
		if (gameState)
		{
			gameState->OnScoreBoardUpdate.AddDynamic(this, &ARCDeathMatchPC::OnScoreBoardUpdateCall);
			gameState->OnShowFinaleStat.AddDynamic(this, &ARCDeathMatchPC::OnFinaleScoreData);
		}
	}
}

void ARCDeathMatchPC::CreateCharacter()
{
	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			ARCCharacter* character = Cast<ARCCharacter>(GM->SpawnCharacter(CharacterClass));
			if (character)
			{
				Possess(character);
				EnableInput(this);
				
				auto Attrib = character->GetAttributes();
				if (Attrib)
				{
					Attrib->OnCharacterKilled.AddDynamic(this, &ARCDeathMatchPC::CharacterKilled);
					Attrib->OnHealthChanged.AddDynamic(this, &ARCDeathMatchPC::HealthUpdate);
					HealthUpdate(Attrib->GetHealth());
				}

			}
			
		}
	}
}

void ARCDeathMatchPC::Server_CreateCharacter_Implementation(TSubclassOf<ARCCharacter> charClass)
{
	CharacterClass = charClass;
	CreateCharacter();
}

UClass* ARCDeathMatchPC::GetCharacterClass() const
{
	return CharacterClass;
}

void ARCDeathMatchPC::Client_Init_Implementation()
{
	if (IsLocalController())
	{
		URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gameInst)
		{
			FPlayerData data = gameInst->GetPlayerData();
			Server_SetPlayerData(data);
			CharacterClass = data.SelectedCharacterClass;
		}
#if WITH_EDITOR
		CharacterClass = DefaultCharacterClass;
#endif

		Server_CreateCharacter(CharacterClass);

		ARCDeathMatchGameState* gameState = GetWorld()->GetGameState<ARCDeathMatchGameState>();
		if (gameState)
		{
			gameState->Server_UpdateScoreBoard();
		}
	}
}

void ARCDeathMatchPC::TimeUpdate(int32 Min, int32 Sec)
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->UpdateTimer(Min, Sec);
	}
}

void ARCDeathMatchPC::ShowFinaleScore(TArray<FScoreBoardData> data)
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->DisplayFinaleStat(data);
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
	bShowMouseCursor = true;
}

void ARCDeathMatchPC::MatchEnd()
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		character->DisableInput(this);
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
	bShowMouseCursor = true;
}

void ARCDeathMatchPC::CharacterKilled(ACharacter* killer)
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		character->KillCharacter();
		character->DisableInput(this);

		DisableInput(this);

		if (killer && killer != character)
		{
			IScoreBoardInterface* scoreBoardInterface = Cast<IScoreBoardInterface>(killer->GetController());
			if (scoreBoardInterface)
			{
				scoreBoardInterface->AddKillCount();
			}
		}
		
		AddDeathCount();

		ARCDeathMatchGameState* gameState = GetWorld()->GetGameState<ARCDeathMatchGameState>();
		if (gameState)
		{
			gameState->Server_UpdateScoreBoard();
		}

		GetWorld()->GetTimerManager().ClearTimer(RestartDelay);
		GetWorld()->GetTimerManager().SetTimer(RestartDelay, this, &ARCDeathMatchPC::Restart, RestartDelayTime, false);
	}
	
}

void ARCDeathMatchPC::HealthUpdate(float val, ACharacter* source)
{
	Client_UpdateHealthStatus(val, source);
}

void ARCDeathMatchPC::Client_UpdateHealthStatus_Implementation(const float hp, ACharacter* source)
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
		
	}
}
