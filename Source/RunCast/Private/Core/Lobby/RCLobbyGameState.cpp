// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyGameState.h"

ARCLobbyGameState::ARCLobbyGameState()
{
	SetReplicates(true);
}

void ARCLobbyGameState::BeginPlay()
{
	Super::BeginPlay();

	Server_GetMatchCreationData();
	StartSyncServerInfo();
}

ELobbyState ARCLobbyGameState::GetCurrentLobbyState() const
{
	return LobbyState;
}

void ARCLobbyGameState::SetNewLobbyState(ELobbyState newState)
{ 
	LobbyState = newState;
	if (OnLobbyStateChanged.IsBound())
	{
		OnLobbyStateChanged.Broadcast(LobbyState);
	}
}

TArray<FArenaMapData> ARCLobbyGameState::GetMapsData() const
{
	return ArenaDataList;
}

TArray<FArenaMatchData> ARCLobbyGameState::GetMatchesData() const
{
	return MatchDataList;
}

void ARCLobbyGameState::StartSyncServerInfo()
{
	if (HasAuthority())
	{
		URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gameInst)
		{
			FServerInfo info = gameInst->GetRemoteServerInfo();
			if (info.Id != -1)
			{
				SyncServerInfo = info;
			}
		}

		GetWorld()->GetTimerManager().ClearTimer(SyncServerInfoTimer);
		GetWorld()->GetTimerManager().SetTimer(SyncServerInfoTimer, this, &ARCLobbyGameState::StartSyncServerInfo, 0.01f, false, SyncPeriod);
	}
}

FServerInfo ARCLobbyGameState::GetSuncServerInfo() const
{
	return SyncServerInfo;
}



void ARCLobbyGameState::GetMatchCreationData()
{
	if (HasAuthority())
	{
		ARCLobbyGM* GM = Cast<ARCLobbyGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			ArenaDataList = GM->GetArenasData();
			MatchDataList = GM->GetMatchesData();
			LobbyState = GM->GetDefaultLobbyState();
			
		}
	}
	
}


void ARCLobbyGameState::Server_GetMatchCreationData_Implementation()
{
	GetMatchCreationData();
}


void ARCLobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARCLobbyGameState, LobbyState);
	DOREPLIFETIME(ARCLobbyGameState, ArenaDataList);
	DOREPLIFETIME(ARCLobbyGameState, MatchDataList);
	DOREPLIFETIME(ARCLobbyGameState, MaxPlayers);
	DOREPLIFETIME(ARCLobbyGameState, SyncServerInfo);
}