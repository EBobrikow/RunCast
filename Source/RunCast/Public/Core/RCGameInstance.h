// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tools/Server/ConnectionManager.h"
#include "Tools/Server/ServerManager.h"
#include "Tools/SaveGame/SaveManager.h"
#include "GameFramework/GameModeBase.h"
#include "RCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void StartSoloGame();

	UFUNCTION(BlueprintCallable)
	void ExitToMainMenu();

	UFUNCTION(BlueprintCallable)
	UServerManager* GetServerManager();

	UFUNCTION(BlueprintCallable)
	USaveManager* GetSaveManager();

	UFUNCTION(BlueprintCallable)
	void StartHeartBeat(AGameModeBase* gameMode);

	UFUNCTION()
	void SetCurrentServerInfo(FServerInfo servInfo);

	UFUNCTION()
	void SetRemoteServerInfo(FServerInfo servInfo);

	UFUNCTION()
	FServerInfo GetRemoteServerInfo() const;

	UFUNCTION()
	FPlayerData GetPlayerData() const;

	UFUNCTION()
	void SetPlayerData(const FPlayerData& name);
	
	UPROPERTY()
	int32 ConnectedPlayersNum = 0;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSoloGame;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	FPlayerData LocalPlayerData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UServerManager* ServerManager = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USaveManager* SaveManager = nullptr;

	UPROPERTY()
	FServerInfo CurrentServerInfo = FServerInfo();

	UPROPERTY()
	FServerInfo RemoteServerInfo = FServerInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float HeartBeatWaitRate = 0.5f;

	UPROPERTY()
	FTimerHandle HeartBeatWaitTimer;

	UPROPERTY()
	AGameModeBase* cashedGameMode;

	UFUNCTION()
	void HeartBeatPing();

	UFUNCTION()
	void HeartBeatPong(FServerInfo servInfo);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map names")
	FString MainMenuMapName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map names")
	FString SoloGameMapName;
};
