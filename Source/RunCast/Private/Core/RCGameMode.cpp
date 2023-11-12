// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameMode.h"
#include "Core/RCPlayerController.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void ARCGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ARCGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (OnPlayerLogin.IsBound())
	{
		OnPlayerLogin.Broadcast(NewPlayer);
	}

	URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->ConnectedPlayersNum++;
	}
	
}

void ARCGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (OnPlayerLogout.IsBound())
	{
		OnPlayerLogout.Broadcast(Exiting);
	}

	URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->ConnectedPlayersNum--;
		if (GameInstance->ConnectedPlayersNum == 0)
		{
			FServerInfo info = GameInstance->GetRemoteServerInfo();
			if (info.Id != -1)
			{
				GameInstance->GetServerManager()->RequestCloseServer(info.Id);
#if UE_SERVER
				FGenericPlatformMisc::RequestExit(false);
#endif
			}
			
		}
	}
}

float ARCGameMode::GetMatchDuration()
{
	return MatchDuration;
}

void ARCGameMode::StartMatchDelay()
{
	GetWorld()->GetTimerManager().SetTimer(StartDelayTimer, this, &ARCGameMode::MatchStart, StartDelay, false);
}

void ARCGameMode::GetCurrentMatchTime(int32& Min, int32& Sec)
{
	Min = CurrentMinutes;
	Sec = CurrentSeconds;
}

void ARCGameMode::MatchStart()
{
	CurrentMinutes = MatchDuration;
	CurrentSeconds = 0;

	GetWorld()->GetTimerManager().SetTimer(TimeCountTimer, this, &ARCGameMode::TimeCount, 1.0f, true);

	if (OnMatchBegin.IsBound())
	{
		OnMatchBegin.Broadcast();
	}
}

void ARCGameMode::TimeCount()
{
	if (CurrentMinutes == 0 && CurrentSeconds == 0)
	{
		if (OnMatchEnd.IsBound())
		{
			OnMatchEnd.Broadcast();
		}
		GetWorld()->GetTimerManager().ClearTimer(TimeCountTimer);
		return;
	}

	if (CurrentSeconds == 0)
	{
		CurrentMinutes -= 1;
		CurrentSeconds = 59;
	}
	else
	{
		CurrentSeconds -= 1;
	}

	if (OnTimeUpdate.IsBound())
	{
		OnTimeUpdate.Broadcast(CurrentMinutes, CurrentSeconds);
	}
}
