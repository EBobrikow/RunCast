// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/PlayerController.h"
#include "Core/RCPlayerController.h"
#include "RCLobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCLobbyPC : public ARCPlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_SetNewLobbyState(const ELobbyState& state);

	UFUNCTION(Server, Reliable)
	void Server_TryRunMatch();

	UFUNCTION(Server, Reliable)
	void Server_SetupMatchConfig(const FArenaMapData& arena, const FArenaMatchData& match);

	UFUNCTION()
	void PlayerReadyClicked();

	UFUNCTION()
	void AddBotClicked(UClass* BotCharClass);

	UFUNCTION(Server, Reliable)
	void Server_AddBot(const FPlayerData& AIPlayerData);

	UFUNCTION()
	void RemoveBotClicked();

	UFUNCTION(Server, Reliable)
	void Server_RemoveBot();

	UFUNCTION(Server, Reliable)
	void Server_CreateMatchClicked(const FArenaMapData& arena, const FArenaMatchData& match, int32 maxPlayers);

};
