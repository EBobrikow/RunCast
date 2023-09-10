// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "Core/Lobby/RCLobbyGM.h"
#include "Tools/Globals.h"
#include "RCLobbyGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyStateChanged, ELobbyState, NewState);

UCLASS()
class RUNCAST_API ARCLobbyGameState : public AGameState
{
	GENERATED_BODY()

public:

	ARCLobbyGameState();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ELobbyState GetCurrentLobbyState() const;

	UFUNCTION(BlueprintCallable)
	void SetNewLobbyState(ELobbyState newState);

	
	UPROPERTY()
	FOnLobbyStateChanged OnLobbyStateChanged;

	UFUNCTION()
	TArray<FArenaMapData> GetMapsData() const;

	UFUNCTION()
	TArray<FArenaMatchData> GetMatchesData() const;
	

protected:

	UFUNCTION(Server, Reliable)
	void Server_GetMatchCreationData();

	UPROPERTY(Replicated)
	TEnumAsByte<ELobbyState> LobbyState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	TArray<FArenaMapData> ArenaDataList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	TArray<FArenaMatchData> MatchDataList;
	
	UPROPERTY(Replicated)
	int32 MaxPlayers;

private: 

	UFUNCTION()
	void GetMatchCreationData();

	
};
