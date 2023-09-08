// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "Core/Lobby/RCLobbyGM.h"
#include "RCLobbyGameState.generated.h"

UENUM(BlueprintType)
enum class ELobbyState : uint8
{
	Entrance,
	DeathMatchLobby,
};


UCLASS()
class RUNCAST_API ARCLobbyGameState : public AGameState
{
	GENERATED_BODY()

public:

	ARCLobbyGameState();
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	TEnumAsByte<ELobbyState> LobbyState;
	
};
