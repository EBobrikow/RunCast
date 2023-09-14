// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameInstance.h"
#include "Kismet/GameplayStatics.h"

void URCGameInstance::StartSoloGame()
{
	bIsSoloGame = true;
	UGameplayStatics::OpenLevel(this,FName(SoloGameMapName));
}

void URCGameInstance::ExitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName(MainMenuMapName));
}

UServerManager* URCGameInstance::GetServerManager()
{
	if (ServerManager == nullptr)
	{
		ServerManager = NewObject<UServerManager>(this);
	}
	return ServerManager;
}

USaveManager* URCGameInstance::GetSaveManager()
{
	if (!SaveManager)
	{
		SaveManager = NewObject<USaveManager>(this);
	}
	return SaveManager;
}



void URCGameInstance::StartHeartBeat(AGameModeBase* gameMode)
{
	cashedGameMode = gameMode;
	GetServerManager()->OnCurrentServerInfoRecieved.Clear();
	GetServerManager()->OnCurrentServerInfoRecieved.AddDynamic(this, &URCGameInstance::HeartBeatPong);

	HeartBeatPing();
}

void URCGameInstance::SetCurrentServerInfo(FServerInfo servInfo)
{
#if UE_SERVER
	CurrentServerInfo = servInfo;
#endif
}

void URCGameInstance::SetRemoteServerInfo(FServerInfo servInfo)
{
	RemoteServerInfo = servInfo;
}

FServerInfo URCGameInstance::GetRemoteServerInfo() const
{
	return RemoteServerInfo;
}

FPlayerData URCGameInstance::GetPlayerData() const
{
	return LocalPlayerData;
}

void URCGameInstance::SetPlayerData(const FPlayerData& name)
{
	LocalPlayerData = name;
}


void URCGameInstance::HeartBeatPing()
{
	if (CurrentServerInfo.Id == -1)
	{
		if (cashedGameMode)
		{
			cashedGameMode->GetWorld()->GetTimerManager().ClearTimer(HeartBeatWaitTimer);
			cashedGameMode->GetWorld()->GetTimerManager().SetTimer(HeartBeatWaitTimer, this, &URCGameInstance::HeartBeatPing, 0.01f, false, HeartBeatWaitRate);
		}
	}
	else
	{
		GetServerManager()->HeartBeatSend(CurrentServerInfo);
	}
}

void URCGameInstance::HeartBeatPong(FServerInfo servInfo)
{
	RemoteServerInfo = servInfo;
	if (cashedGameMode)
	{
		cashedGameMode->GetWorld()->GetTimerManager().ClearTimer(HeartBeatWaitTimer);
		cashedGameMode->GetWorld()->GetTimerManager().SetTimer(HeartBeatWaitTimer, this, &URCGameInstance::HeartBeatPing, 0.01f, false, HeartBeatWaitRate);
	}
}
