// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Abilities/RCAttributeSet.h"
#include "Core/RCGameInstance.h"

ARCDeathMatchPC::ARCDeathMatchPC()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

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
			gameState->OnCharacterKillAnounce.AddDynamic(this, &ARCDeathMatchPC::CharacterKillAnounce);
		}

		
	}
	

	Client_StartBackgroundMusic();
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

void ARCDeathMatchPC::CharacterKilled(AActor* killer)
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		character->KillCharacter();
		character->DisableInput(this);

		DisableInput(this);

		if (killer && killer != character)
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
		Client_ClearAbilityCooldownsUI();

		ARCDeathMatchGameState* gameState = GetWorld()->GetGameState<ARCDeathMatchGameState>();
		if (gameState)
		{
			gameState->Server_UpdateScoreBoard();
			gameState->Server_AnounceCharacterKilled(killer, character);
		}

		GetWorld()->GetTimerManager().ClearTimer(RestartDelay);
		GetWorld()->GetTimerManager().SetTimer(RestartDelay, this, &ARCDeathMatchPC::Restart, RestartDelayTime, false);
	}
	
}

void ARCDeathMatchPC::HealthUpdate(float val, AActor* source)
{
	Client_UpdateHealthStatus(val, source);
}

void ARCDeathMatchPC::Client_UpdateHealthStatus_Implementation(const float hp, AActor* source)
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->UpdateHealthBar(hp);
		if (source)
		{
			hud->DisplayDamageDirection(source);
		}
		
	}
}

void ARCDeathMatchPC::Client_ClearAbilityCooldownsUI_Implementation()
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->ClearCooldowns();
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

void ARCDeathMatchPC::Client_CharacterKillAnounce_Implementation(const FString& killerName, EWeaponIconType weaponIconType, const FString& victimName)
{
	ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
	if (hud)
	{
		hud->KillAnnounce(killerName, weaponIconType, victimName);
	}
}

void ARCDeathMatchPC::CharacterKillAnounce(FString killerName, EWeaponIconType weaponIconType, FString victimName)
{
	Client_CharacterKillAnounce(killerName, weaponIconType, victimName);
}

void ARCDeathMatchPC::PlayMusicList()
{
	if (AudioComponent && MusicList.Num() > 0)
	{
		int32 randInd = FMath::RandRange(0, MusicList.Num() - 1);
		USoundBase* sound = MusicList[randInd];
		MusicList.RemoveAt(randInd);
		AudioComponent->SetSound(sound);
		AudioComponent->OnAudioFinished.Clear();
		AudioComponent->OnAudioFinished.AddDynamic(this, &ARCDeathMatchPC::PlayMusicList);
		AudioComponent->Play();
	}
}

void ARCDeathMatchPC::Client_StartBackgroundMusic_Implementation()
{
	if (URCGameInstance* GI = GetWorld()->GetGameInstance<URCGameInstance>())
	{
		if (UBackgroundMusicContaner* musicContainer = GI->GetBackgroundMusicContainer())
		{
			MusicList = musicContainer->BackgroundMusicList;
			PlayMusicList();
		}

	}
}
