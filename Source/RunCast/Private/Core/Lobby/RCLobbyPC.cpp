// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyPC.h"
#include "Core/Lobby/RCLobbyGameState.h"

void ARCLobbyPC::BeginPlay()
{
	Super::BeginPlay();
}

void ARCLobbyPC::Server_TryRunMatch_Implementation()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		GameState->Server_TryStartMatch();
	}
}

void ARCLobbyPC::Server_SetupMatchConfig_Implementation(const FArenaMapData& arena, const FArenaMatchData& match)
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		GameState->Server_SetCurrentMatchAndMap(arena, match);
	}
}

void ARCLobbyPC::PlayerReadyClicked()
{
	if (PlayerData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
	{
		Server_UpdatePlayerData(PlayerData);
		Server_TryRunMatch();
		return;
	}


	if (PlayerData.PlayerReady == ELobbyPlayerReady::Ready)
	{
		PlayerData.PlayerReady = ELobbyPlayerReady::Idle;
	}
	else
	{
		PlayerData.PlayerReady = ELobbyPlayerReady::Ready;
		
		
	}
	Server_UpdatePlayerData(PlayerData);
	
}

void ARCLobbyPC::AddBotClicked(UClass* BotCharClass)
{
	FPlayerData AIPlayerData;
	AIPlayerData.PlayerAuthority = ELobbyPlayerAuthority::AIBot;
	AIPlayerData.PlayerName = "Bot";
	AIPlayerData.PlayerReady = ELobbyPlayerReady::Ready;
	AIPlayerData.SelectedCharacterClass = BotCharClass;
	Server_AddBot(AIPlayerData);
}

void ARCLobbyPC::Server_AddBot_Implementation(const FPlayerData& AIPlayerData)
{
	if (HasAuthority() && PlayerData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
	{
		ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
		if (GameState)
		{
			GameState->Server_AddAIBot(AIPlayerData);

		}
	}
}

void ARCLobbyPC::RemoveBotClicked()
{
	Server_RemoveBot();
}

void ARCLobbyPC::Server_RemoveBot_Implementation()
{
	if (HasAuthority() && PlayerData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
	{
		ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
		if (GameState)
		{
			GameState->Server_RemoveAIBot();

		}
	}
}

void ARCLobbyPC::Server_CreateMatchClicked_Implementation(const FArenaMapData& arena, const FArenaMatchData& match, int32 maxPlayers)
{
	if (HasAuthority() && PlayerData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
	{
		ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
		if (GameState)
		{

			FServerInfo info = GameState->GetSyncServerInfo();

			info.MapName = arena.MapName;
			info.MatchType = match.MatchName;
			info.MaxPlayers = maxPlayers;
			GameState->Server_UpdateServerInfo(info);

		}

		Server_SetupMatchConfig(arena, match);

		if (match.MatchType == EMatchType::DeathMatch)
		{
			Server_SetNewLobbyState(ELobbyState::DeathMatchLobby);
		}
	}
	
}

void ARCLobbyPC::Server_SetNewLobbyState_Implementation(const ELobbyState& state)
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		GameState->Server_SetNewLobbyState(state);
	}
	
}
