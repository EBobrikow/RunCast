// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tools/Server/ConnectionManager.h"
#include "Tools/Server/ServerManager.h"
#include "Tools/SaveGame/SaveManager.h"
#include "GameFramework/GameModeBase.h"
#include "Tools/DefaultValuesContainer.h"
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
	void ExitGame();

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
	FServerInfo GetCurrentServerInfo() const;

	UFUNCTION()
	FPlayerData GetPlayerData() const;

	UFUNCTION()
	void SetPlayerData(const FPlayerData& name);
	
	UPROPERTY()
	int32 ConnectedPlayersNum = 0;

	UFUNCTION()
	void SetAIPlayersData(TArray<FPlayerData> data);

	UFUNCTION()
	TArray<FPlayerData> GetAIPlayersData() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSoloGame;

	UFUNCTION()
	UDefaultValuesContainer* GetDefaultValuesContaner() const;

protected:

	virtual void Init() override;

	

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	FPlayerData LocalPlayerData;

	UPROPERTY()
	UServerManager* ServerManager = nullptr;

	UPROPERTY()
	USaveManager* SaveManager = nullptr;

	UPROPERTY()
	FServerInfo CurrentServerInfo = FServerInfo();

	UPROPERTY()
	FServerInfo RemoteServerInfo = FServerInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float HeartBeatWaitRate = 1.0f;

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

	UPROPERTY()
	TArray<FPlayerData> AIPlayersDataList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UDefaultValuesContainer> DefaultValuesContainerClass;
};
