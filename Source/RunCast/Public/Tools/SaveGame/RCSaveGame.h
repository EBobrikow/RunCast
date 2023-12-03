// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Tools/Globals.h"
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

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> Graphics;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> Shadow;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> Aliasing;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> PostProcessing;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> ViewDistance;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> Texture;

	UPROPERTY()
	TEnumAsByte<ESettingsQuality> Effects;
};
