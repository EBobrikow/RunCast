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

	ARCLobbyGM* GM = Cast<ARCLobbyGM>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->OnLobbyPlayerLogin.AddDynamic(this, &ARCLobbyGameState::OnPlayerLogin);
		GM->OnLobbyPlayerLogout.AddDynamic(this, &ARCLobbyGameState::OnPlayerLogout);
	}
	
}

ELobbyState ARCLobbyGameState::GetCurrentLobbyState() const
{
	return LobbyState;
}

void ARCLobbyGameState::Client_SetSyncServerInfo_Implementation(const FServerInfo& info)
{
	SyncServerInfo = info;
}

void ARCLobbyGameState::Server_AddAIBot_Implementation(const FPlayerData& AIPlayerData)
{
	FPlayerData tmp = AIPlayerData;
	tmp.PlayerName += FString::FromInt(AIDataList.Num() + 1);
	AIDataList.Add(tmp);
	Server_UpdatePlayerList();
}

void ARCLobbyGameState::Server_RemoveAIBot_Implementation()
{
	if (AIDataList.Num() > 0)
	{
		AIDataList.RemoveAt(AIDataList.Num() - 1);
		Server_UpdatePlayerList();
	}
}

TArray<FArenaMapData> ARCLobbyGameState::GetMapsData()
{
	GetMatchCreationData();
	return ArenaDataList;
}

TArray<FArenaMatchData> ARCLobbyGameState::GetMatchesData()
{
	GetMatchCreationData();
	return MatchDataList;
}

void ARCLobbyGameState::StartSyncServerInfo()
{
	if (HasAuthority())
	{
		URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gameInst)
		{
			FServerInfo info = gameInst->GetCurrentServerInfo();
			if (info.Id != -1)
			{
				SyncServerInfo = info;
				Client_SetSyncServerInfo(info);
			}
		}

		GetWorld()->GetTimerManager().ClearTimer(SyncServerInfoTimer);
		GetWorld()->GetTimerManager().SetTimer(SyncServerInfoTimer, this, &ARCLobbyGameState::StartSyncServerInfo, 0.01f, false, SyncPeriod);
	}
}

FServerInfo ARCLobbyGameState::GetSyncServerInfo() const
{
	return SyncServerInfo;
}

TArray<FPlayerData> ARCLobbyGameState::GetPlayerDataList() const
{
	return PlayersDataList;
}

void ARCLobbyGameState::OnPlayerLogin(APlayerController* NewPlayer)
{
	if (HasAuthority())
	{
		PlayersDataList.Empty();
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
			if (Controller)
			{
				PlayersDataList.Add(Controller->GetPlayerData());
			}
		}
		NetMulticast_BroadcastPlayersList(PlayersDataList);
	}

}

void ARCLobbyGameState::OnPlayerLogout(AController* Exiting)
{
	if (HasAuthority())
	{
		PlayersDataList.Empty();
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
			if (Controller)
			{
				PlayersDataList.Add(Controller->GetPlayerData());
			}
		}
		NetMulticast_BroadcastPlayersList(PlayersDataList);
	}
}


void ARCLobbyGameState::GetMatchCreationData()
{
	bool solo = false;
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr)
	{
		solo = GameInstancePtr->bIsSoloGame;
	}

	if (HasAuthority() || solo)
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

void ARCLobbyGameState::Server_UpdatePlayerList_Implementation()
{
	
	PlayersDataList.Empty();
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
		if (Controller)
		{
			PlayersDataList.Add(Controller->GetPlayerData());
		}
	}
	for (FPlayerData data : AIDataList)
	{
		PlayersDataList.Add(data);
	}

	NetMulticast_BroadcastPlayersList(PlayersDataList);
	
}

void ARCLobbyGameState::Server_TryStartMatch_Implementation()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
		if (Controller)
		{
			FPlayerData pData = Controller->GetPlayerData();
			if (pData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
			{
				continue;
			}

			if (pData.PlayerReady != ELobbyPlayerReady::Ready)
			{
				UE_LOG(LogTemp, Warning, TEXT("ARCLobbyGameState::Server_TryStartMatch Player %s not ready"), *pData.PlayerName);
				return;
			}
		}
	}

	URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInst)
	{
		gameInst->SetAIPlayersData(AIDataList);
	}

	FString route = "";
	route += CurrentMap.MapPath + "?game=" + CurrentMatch.MatchGameModePath;
	ARCLobbyGM* GM = Cast<ARCLobbyGM>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->StartTravel(route);
	}

}

void ARCLobbyGameState::Server_SetNewLobbyState_Implementation(const ELobbyState& newState)
{

	LobbyState = newState;
	NetMulticast_BroadcastLobbyState(newState);
	
}

void ARCLobbyGameState::Server_SetCurrentMatchAndMap_Implementation(const FArenaMapData& arena, const FArenaMatchData& match)
{
	CurrentMap = arena;
	CurrentMatch = match;
}

void ARCLobbyGameState::Server_UpdateServerInfo_Implementation(const FServerInfo& info)
{
	if (HasAuthority())
	{
		FServerInfo local = info;
		URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gameInst)
		{
			local.CurrPlayers = gameInst->ConnectedPlayersNum;
			gameInst->SetCurrentServerInfo(local);
			gameInst->SetRemoteServerInfo(local);
		}
	}
}

void ARCLobbyGameState::Server_GetMatchCreationData_Implementation()
{
	GetMatchCreationData();
}

void ARCLobbyGameState::NetMulticast_BroadcastPlayersList_Implementation(const TArray<FPlayerData>& list)
{
	if (OnPlayersListChanged.IsBound())
	{
		OnPlayersListChanged.Broadcast(list);
	}
}

void ARCLobbyGameState::NetMulticast_BroadcastLobbyState_Implementation(const ELobbyState& newState)
{
	if (OnLobbyStateChanged.IsBound())
	{
		OnLobbyStateChanged.Broadcast(newState);
	}
}



void ARCLobbyGameState::OnRep_PlayerList()
{
	if (OnPlayersListChanged.IsBound())
	{
		OnPlayersListChanged.Broadcast(PlayersDataList);
	}
}

void ARCLobbyGameState::OnRep_SyncServerInfo()
{
	
	if (OnSyncInfoChanged.IsBound())
	{
		OnSyncInfoChanged.Broadcast(SyncServerInfo);
	}
	
	
}

void ARCLobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARCLobbyGameState, LobbyState);
	DOREPLIFETIME(ARCLobbyGameState, ArenaDataList);
	DOREPLIFETIME(ARCLobbyGameState, MatchDataList);
	DOREPLIFETIME(ARCLobbyGameState, MaxPlayers);
	DOREPLIFETIME(ARCLobbyGameState, SyncServerInfo);
	DOREPLIFETIME(ARCLobbyGameState, PlayersDataList);
	DOREPLIFETIME(ARCLobbyGameState, CurrentMap);
	DOREPLIFETIME(ARCLobbyGameState, CurrentMatch);
	
}