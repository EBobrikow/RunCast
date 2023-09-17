// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/GameMode.h"
#include "Core/RCGameMode.h"
#include "Core/RCPlayerController.h"
#include "Tools/Globals.h"
#include "RCLobbyGM.generated.h"

class ARCLobbyGameState;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyPlayerLogin, APlayerController*, playerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyPlayerLogout, AController*, exitController);

UCLASS()
class RUNCAST_API ARCLobbyGM : public ARCGameMode
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

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY()
	FOnLobbyPlayerLogin OnLobbyPlayerLogin;

	UPROPERTY()
	FOnLobbyPlayerLogout OnLobbyPlayerLogout;

	UFUNCTION()
	void StartTravel(const FString& route);

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
	void CurrentServerInfoRequestHandle(FServerInfo servInfo);

	UFUNCTION()
	void GetServerInfoWhenReady();

	UPROPERTY()
	FTimerHandle InfoReuestTimer;

private: 


};
