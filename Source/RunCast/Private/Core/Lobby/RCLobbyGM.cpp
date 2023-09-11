// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyGM.h"

void ARCLobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	

#if UE_SERVER
	GetServerInfoWhenReady();
	if (GameInstance)
	{
		GameInstance->StartHeartBeat(this);
	}	
#endif
}

ELobbyState ARCLobbyGM::GetDefaultLobbyState() const
{
	return DefaultLobbyState;
}


TArray<FArenaMatchData> ARCLobbyGM::GetMatchesData() const
{
	return MatchDataList;
}

TArray<FArenaMapData> ARCLobbyGM::GetArenasData() const
{
	return ArenaDataList;
}

void ARCLobbyGM::FillCurrentServerInfoRequest()
{
	if (GameInstance)
	{
		int32 port = GetWorld()->URL.Port;
		GameInstance->GetServerManager()->OnCurrentServerInfoRecieved.AddDynamic(this, &ARCLobbyGM::CurrentServerInfoRequestHandle);
		GameInstance->GetServerManager()->RequestSessionInfoByPort(port);
	}
	
}

void ARCLobbyGM::CurrentServerInfoRequestHandle(FServerInfo servInfo)
{
	if (GameInstance)
	{
		GameInstance->GetServerManager()->OnCurrentServerInfoRecieved.Clear();
		GameInstance->SetCurrentServerInfo(servInfo);
	}
}

void ARCLobbyGM::GetServerInfoWhenReady()
{
	if (GameInstance)
	{
		if (!GameInstance->GetServerManager()->GetConnectionManager()->IsConnected())
		{
			GetWorld()->GetTimerManager().ClearTimer(InfoReuestTimer);
			GetWorld()->GetTimerManager().SetTimer(InfoReuestTimer, this, &ARCLobbyGM::GetServerInfoWhenReady, 0.01f, false, 0.5f);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(InfoReuestTimer);
			FillCurrentServerInfoRequest();
		}
	}
}
