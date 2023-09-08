// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Core/RCGameInstance.h"

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
};
