// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tools/Globals.h"
#include "UObject/NoExportTypes.h"
#include "RCPlayerListViewContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNCAST_API URCPlayerListViewContainer : public UObject
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerData PlayerData;
	
};
