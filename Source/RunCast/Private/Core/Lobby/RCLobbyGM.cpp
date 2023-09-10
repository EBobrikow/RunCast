// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyGM.h"

void ARCLobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	
#if UE_SERVER
	FillCurrentServerInfoRequest();
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

void ARCLobbyGM::CurrentServerInfoRequestHandle(FCurrentServerInfo servInfo)
{
	if (GameInstance)
	{
		GameInstance->SetCurrentServerInfo(servInfo);
	}
}
