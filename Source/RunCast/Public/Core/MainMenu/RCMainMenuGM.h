// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/GameMode.h"
#include "Core/RCGameMode.h"
#include "Core/RCGameInstance.h"
#include "RCMainMenuGM.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCMainMenuGM : public ARCGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	URCGameInstance* GameInstance = nullptr;

	
};
