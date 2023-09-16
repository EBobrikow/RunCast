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

};
