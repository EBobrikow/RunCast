// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Core/RCGameInstance.h"
#include "Tools/Globals.h"
#include "RCLobbyGM.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCLobbyGM : public AGameMode
{
	GENERATED_BODY()
	
public: 

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ELobbyState GetDefaultLobbyState() const;


	UFUNCTION(BlueprintCallable)
	TArray<FArenaMatchData> GetMatchesData() const;

	UFUNCTION(BlueprintCallable)
	TArray<FArenaMapData> GetArenasData() const;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GM | Lobby settings")
	TEnumAsByte<ELobbyState> DefaultLobbyState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GM | Lobby settings")
	TArray<FArenaMapData> ArenaDataList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GM | Lobby settings")
	TArray<FArenaMatchData> MatchDataList;

	UPROPERTY()
	URCGameInstance* GameInstance = nullptr;

	UFUNCTION()
	void FillCurrentServerInfoRequest();

	UFUNCTION()
	void CurrentServerInfoRequestHandle(FCurrentServerInfo servInfo);

private: 


};
