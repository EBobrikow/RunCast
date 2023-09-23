// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RCDeathMatchHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCDeathMatchHUD : public AHUD
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	
};
