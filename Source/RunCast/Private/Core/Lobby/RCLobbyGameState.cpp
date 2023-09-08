// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyGameState.h"

ARCLobbyGameState::ARCLobbyGameState()
{
	SetReplicates(true);
}

void ARCLobbyGameState::BeginPlay()
{
	Super::BeginPlay();
}


void ARCLobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARCLobbyGameState, LobbyState);
}