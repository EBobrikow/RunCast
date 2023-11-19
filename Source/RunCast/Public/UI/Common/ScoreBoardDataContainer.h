// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Globals.h"
#include "ScoreBoardDataContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNCAST_API UScoreBoardDataContainer : public UObject
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FScoreBoardData ScoreData;
	
};
