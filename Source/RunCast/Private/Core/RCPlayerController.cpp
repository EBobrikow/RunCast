// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Lobby/RCLobbyGameState.h"
#include "Core/RCGameMode.h"
#include "Characters/RCCharacter.h"
#include "UI/Common/InGameHUD.h"


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
		

	}

	if (HasAuthority())
	{
		ARCGameMode* GM = Cast<ARCGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->OnTimeUpdate.AddDynamic(this, &ARCPlayerController::Client_TimerUpdate);
		}
	}
}


void ARCPlayerController::Server_SetPlayerData_Implementation(const FPlayerData& playerData)
{
	if (HasAuthority())
	{
		PlayerData = playerData;
		ScoreData.PlayerName = PlayerData.PlayerName;
	}

	Client_PreservePlayerData(playerData);
}

FPlayerData ARCPlayerController::GetPlayerData()
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr && IsLocalController())
	{
		PlayerData = GameInstancePtr->GetPlayerData();
	}
	return PlayerData;
}

void ARCPlayerController::SetPlayerData(const FPlayerData& data)
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr && IsLocalController())
	{
		GameInstancePtr->SetPlayerData(data);
		PlayerData = data;
	}
}

void ARCPlayerController::Client_TimerUpdate_Implementation(int32 Min, int32 Sec)
{
	TimeUpdate(Min, Sec);
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

		ScoreData.PlayerName = PlayerData.PlayerName;
		ARCGameState* gameState = GetWorld()->GetGameState<ARCGameState>();
		if (gameState)
		{
			gameState->Server_UpdateScoreBoard();
		}
	}
}

void ARCPlayerController::UpdatePlayerToServer()
{
	Server_UpdatePlayerData(PlayerData);
}

void ARCPlayerController::ShowInGameMenu()
{
	ShowMenu();
}

void ARCPlayerController::ShowScoreBoard()
{
	AInGameHUD* hud = Cast<AInGameHUD>(GetHUD());
	if (hud)
	{
		hud->ShowScoreBoard();
	}
}

void ARCPlayerController::HideScoreBoard()
{
	AInGameHUD* hud = Cast<AInGameHUD>(GetHUD());
	if (hud)
	{
		hud->HideScoreBoard();
	}
}

void ARCPlayerController::UpdateScoreBoard(TArray<FScoreBoardData> data)
{
	AInGameHUD* hud = Cast<AInGameHUD>(GetHUD());
	if (hud)
	{
		hud->UpdateScoreBoardData(data);
	}
}

void ARCPlayerController::ShowMenu()
{
	AInGameHUD* hud = Cast<AInGameHUD>(GetHUD());
	if (hud)
	{
		hud->ShowGameMenu(this);
	}
}

void ARCPlayerController::TimeUpdate(int32 Min, int32 Sec)
{
}

void ARCPlayerController::AddKillCount()
{
	ScoreData.KillCount += 1;
}

void ARCPlayerController::AddDeathCount()
{
	ScoreData.DeathCount += 1;
}

FScoreBoardData ARCPlayerController::GetScoreBoardData()
{
	return ScoreData;
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
	DOREPLIFETIME(ARCPlayerController, ScoreData);
}