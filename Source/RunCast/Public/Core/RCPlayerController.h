// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/RCGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "RCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 

	ARCPlayerController();
	virtual void BeginPlay() override;


	UFUNCTION(Server, Reliable)
	void Server_SetPlayerData(const FPlayerData& playerData);

	virtual FPlayerData GetPlayerData();

	UFUNCTION(Client, Reliable)
	void Client_PreservePlayerData(const FPlayerData& playerData);


protected: 

	UPROPERTY(Replicated)
	FPlayerData PlayerData;
};
