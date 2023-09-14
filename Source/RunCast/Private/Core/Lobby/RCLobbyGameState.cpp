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

void ARCLobbyGameState::Server_SetNewLobbyState_Implementation(ELobbyState newState)
{ 
	if (HasAuthority())
	{
		LobbyState = newState;
		NetMulticast_BroadcastLobbyState();
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

void ARCLobbyGameState::NetMulticast_BroadcastPlayersList_Implementation()
{
	if (OnPlayersListChanged.IsBound())
	{
		OnPlayersListChanged.Broadcast(PlayersDataList);
	}
}

void ARCLobbyGameState::Server_UpdateServerInfo_Implementation(FServerInfo info)
{
	if (HasAuthority())
	{
		URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gameInst)
		{
			gameInst->SetCurrentServerInfo(info);
		}
	}
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
		NetMulticast_BroadcastPlayersList();
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
		NetMulticast_BroadcastPlayersList();
	}
}

void ARCLobbyGameState::NetMulticast_BroadcastLobbyState_Implementation()
{
	if (OnLobbyStateChanged.IsBound())
	{
		OnLobbyStateChanged.Broadcast(LobbyState);
	}
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
	DOREPLIFETIME(ARCLobbyGameState, PlayersDataList);
}