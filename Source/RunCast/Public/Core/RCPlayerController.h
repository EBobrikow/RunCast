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

	virtual FPlayerData GetPlayerData();

	virtual void SetPlayerData(const FPlayerData& data);

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerData(const FPlayerData& playerData);

	UFUNCTION(Client, Reliable)
	void Client_TimerUpdate(int32 Min, int32 Sec);

	UFUNCTION(Client, Reliable)
	void Client_PreservePlayerData(const FPlayerData& playerData);

	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerData(const FPlayerData& playerData);

	UFUNCTION(Client, Reliable)
	void Client_SetupPlayerData(const FPlayerData& playerData);

	UFUNCTION()
	void UpdatePlayerToServer();

	UFUNCTION(BlueprintCallable)
	void ShowInGameMenu();

protected: 

	UPROPERTY(Replicated)
	FPlayerData PlayerData;

	virtual void ShowMenu();

	virtual void TimeUpdate(int32 Min, int32 Sec);

	//virtual void LightAttack(bool val) override;
};
