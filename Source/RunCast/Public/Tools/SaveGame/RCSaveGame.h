// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RCSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public: 

	UPROPERTY()
	float MusicVoluem;

	UPROPERTY()
	float AmbientVoluem;

	UPROPERTY()
	float EffectsVoluem;
};
