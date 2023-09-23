// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "Core/Lobby/RCLobbyGM.h"
#include "Tools/Globals.h"
#include "RCLobbyGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyStateChanged, ELobbyState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayersListChanged, TArray<FPlayerData>, playersList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSyncInfoChanged, FServerInfo, syncServerInfo);

UCLASS()
class RUNCAST_API ARCLobbyGameState : public AGameState
{
	GENERATED_BODY()

public:

	ARCLobbyGameState();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ELobbyState GetCurrentLobbyState() const;

	UFUNCTION(Server, Reliable)
	void Server_SetNewLobbyState(const ELobbyState& newState);

	UFUNCTION(Server, Reliable)
	void Server_UpdateServerInfo(const FServerInfo& info);

	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerList();

	UFUNCTION(Server, Reliable)
	void Server_SetCurrentMatchAndMap(const FArenaMapData& arena, const FArenaMatchData& match);

	UFUNCTION(Server, Reliable)
	void Server_TryStartMatch();

	UFUNCTION(Client, Reliable)
	void Client_SetSyncServerInfo(const FServerInfo& info);

	
	UPROPERTY()
	FOnLobbyStateChanged OnLobbyStateChanged;

	UPROPERTY()
	FOnPlayersListChanged OnPlayersListChanged;

	UPROPERTY()
	FOnSyncInfoChanged OnSyncInfoChanged;

	UFUNCTION()
	TArray<FArenaMapData> GetMapsData() const;

	UFUNCTION()
	TArray<FArenaMatchData> GetMatchesData() const;

	UFUNCTION()
	void StartSyncServerInfo();
	
	UFUNCTION()
	FServerInfo GetSyncServerInfo() const;

	UFUNCTION()
	TArray<FPlayerData> GetPlayerDataList() const;

protected:

	UFUNCTION(Server, Reliable)
	void Server_GetMatchCreationData();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_BroadcastLobbyState(const ELobbyState& newState);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_BroadcastPlayersList(const TArray<FPlayerData>& list);

	

	UFUNCTION()
	void OnPlayerLogin(APlayerController* NewPlayer);

	UFUNCTION()
	void OnPlayerLogout(AController* Exiting);

	UPROPERTY(Replicated)
	TEnumAsByte<ELobbyState> LobbyState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	TArray<FArenaMapData> ArenaDataList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	TArray<FArenaMatchData> MatchDataList;
	
	UPROPERTY(Replicated)
	int32 MaxPlayers;

	UPROPERTY(ReplicatedUsing = OnRep_SyncServerInfo)
	FServerInfo SyncServerInfo;

	UPROPERTY(Replicated)
	FArenaMapData CurrentMap;

	UPROPERTY(Replicated)
	FArenaMatchData CurrentMatch;

	UPROPERTY()
	FTimerHandle SyncServerInfoTimer;

	UPROPERTY()
	float SyncPeriod = 1.0f;

private: 

	UFUNCTION()
	void GetMatchCreationData();

	UFUNCTION()
	void OnRep_PlayerList();

	UFUNCTION()
	void OnRep_SyncServerInfo();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerList)
	TArray<FPlayerData> PlayersDataList;

	
};
