// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

	Client_PreservePlayerData();
}

FPlayerData ARCPlayerController::GetPlayerData()
{
	return PlayerData;
}

void ARCPlayerController::Client_PreservePlayerData_Implementation()
{
	URCGameInstance* GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstancePtr)
	{
		GameInstancePtr->SetPlayerData(PlayerData);
	}
}





void ARCPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARCPlayerController, PlayerData);
}