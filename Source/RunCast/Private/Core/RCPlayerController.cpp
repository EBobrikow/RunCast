// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Lobby/RCLobbyGameState.h"

ARCPlayerController::ARCPlayerController()
{
	bReplicates = true;
}

void ARCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		//bShowMouseCursor = false;
	}
}


void ARCPlayerController::Server_SetPlayerData_Implementation(const FPlayerData& playerData)
{
	if (HasAuthority())
	{
		PlayerData = playerData;
	}

	Client_PreservePlayerData(playerData);
}

FPlayerData ARCPlayerController::GetPlayerData()
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr && !HasAuthority())
	{
		PlayerData = GameInstancePtr->GetPlayerData();
	}
	return PlayerData;
}

void ARCPlayerController::Server_UpdatePlayerData_Implementation(const FPlayerData& playerData)
{
	if (HasAuthority())
	{
		PlayerData = playerData;
		ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
		if (GameState)
		{
			GameState->Server_UpdatePlayerList();
		}
	}
}

void ARCPlayerController::Client_SetupPlayerData_Implementation(const FPlayerData& playerData)
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr)
	{
		FPlayerData data = GameInstancePtr->GetPlayerData();
		PlayerData = playerData;
		PlayerData.PlayerName = data.PlayerName;
		GameInstancePtr->SetPlayerData(PlayerData);
		Server_SetPlayerData(PlayerData);
	}
}

void ARCPlayerController::UpdatePlayerToServer()
{
	Server_UpdatePlayerData(PlayerData);
}

void ARCPlayerController::Client_PreservePlayerData_Implementation(const FPlayerData& playerData)
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr)
	{
		PlayerData = playerData;
		GameInstancePtr->SetPlayerData(PlayerData);
	}
}





void ARCPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARCPlayerController, PlayerData);
}