// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Character/ALSPlayerController.h"
#include "Core/RCPlayerController.h"
#include "RCDeathMatchPC.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCDeathMatchPC : public ARCPlayerController
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void CreateCharacter();
};
