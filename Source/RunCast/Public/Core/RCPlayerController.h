// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/RCGameInstance.h"
#include "Character/ALSPlayerController.h"
//#include "Core/Lobby/RCLobbyGameState.h"
#include "Net/UnrealNetwork.h"
#include "RCPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class RUNCAST_API ARCPlayerController : public AALSPlayerController
{
	GENERATED_BODY()
	
public: 

	ARCPlayerController();
	virtual void BeginPlay() override;


	UFUNCTION(Server, Reliable)
	void Server_SetPlayerData(const FPlayerData& playerData);

	virtual FPlayerData GetPlayerData();

	virtual void SetPlayerData(const FPlayerData& data);

	UFUNCTION(Client, Reliable)
	void Client_PreservePlayerData(const FPlayerData& playerData);

	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerData(const FPlayerData& playerData);

	UFUNCTION(Client, Reliable)
	void Client_SetupPlayerData(const FPlayerData& playerData);

	UFUNCTION()
	void UpdatePlayerToServer();

	//UFUNCTION(Server, Reliable)
	//void Server_LightAttack(const bool val);

protected: 

	UPROPERTY(Replicated)
	FPlayerData PlayerData;

	//virtual void LightAttack(bool val) override;
};
