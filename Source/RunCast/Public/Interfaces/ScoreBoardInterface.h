// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Globals.h"
#include "ScoreBoardInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UScoreBoardInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IScoreBoardInterface
{
	GENERATED_BODY()

public:

	virtual void AddKillCount();

	virtual void AddDeathCount();

	virtual FScoreBoardData GetScoreBoardData();

};