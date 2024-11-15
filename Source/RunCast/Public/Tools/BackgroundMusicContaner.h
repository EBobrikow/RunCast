// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundBase.h"
#include "BackgroundMusicContaner.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RUNCAST_API UBackgroundMusicContaner : public UObject
{
	GENERATED_BODY()

public: 

	UBackgroundMusicContaner();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USoundBase*> BackgroundMusicList;
	
};
