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

void URCGameInstance::ExitGame()
{
	GetServerManager()->GetConnectionManager()->CloseConnection();
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
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
	UE_LOG(LogTemp, Warning, TEXT("URCGameInstance::StartHeartBeat"));
	cashedGameMode = gameMode;
	GetServerManager()->OnHeartBeatInfoRecieved.Clear();
	GetServerManager()->OnHeartBeatInfoRecieved.AddUniqueDynamic(this, &URCGameInstance::HeartBeatPong);

	HeartBeatPing();
}

void URCGameInstance::SetCurrentServerInfo(FServerInfo servInfo)
{
#if UE_SERVER
	UE_LOG(LogTemp, Warning, TEXT("URCGameInstance::SetCurrentServerInfo SERVER"));
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

FServerInfo URCGameInstance::GetCurrentServerInfo() const
{
#if UE_SERVER
	return CurrentServerInfo;
#endif
	return FServerInfo();
}

FPlayerData URCGameInstance::GetPlayerData() const
{
	return LocalPlayerData;
}

void URCGameInstance::SetPlayerData(const FPlayerData& name)
{
	LocalPlayerData = name;
}

void URCGameInstance::SetAIPlayersData(TArray<FPlayerData> data)
{
	AIPlayersDataList = data;
}

TArray<FPlayerData> URCGameInstance::GetAIPlayersData() const
{
	return AIPlayersDataList;
}


void URCGameInstance::HeartBeatPing()
{
	if (CurrentServerInfo.Id == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("URCGameInstance::HeartBeatPing ServerID == -1"));
		if (cashedGameMode)
		{
			cashedGameMode->GetWorld()->GetTimerManager().ClearTimer(HeartBeatWaitTimer);
			cashedGameMode->GetWorld()->GetTimerManager().SetTimer(HeartBeatWaitTimer, this, &URCGameInstance::HeartBeatPing, 0.01f, false, HeartBeatWaitRate);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URCGameInstance::HeartBeatPing No cashed game mode"));
		}
	}
	else
	{
		GetServerManager()->HeartBeatSend(CurrentServerInfo);
	}
}

void URCGameInstance::HeartBeatPong(FServerInfo servInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("URCGameInstance::HeartBeatPong"));
	RemoteServerInfo = servInfo;
	if (cashedGameMode)
	{
		cashedGameMode->GetWorld()->GetTimerManager().ClearTimer(HeartBeatWaitTimer);
		cashedGameMode->GetWorld()->GetTimerManager().SetTimer(HeartBeatWaitTimer, this, &URCGameInstance::HeartBeatPing, 0.01f, false, HeartBeatWaitRate);
	}
}
