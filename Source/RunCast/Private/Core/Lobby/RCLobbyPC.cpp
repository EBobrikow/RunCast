// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyPC.h"
#include "Core/Lobby/RCLobbyGameState.h"

void ARCLobbyPC::BeginPlay()
{
	Super::BeginPlay();
}

void ARCLobbyPC::Server_SetNewLobbyState_Implementation(const ELobbyState& state)
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		GameState->Server_SetNewLobbyState(state);
	}
	
}
