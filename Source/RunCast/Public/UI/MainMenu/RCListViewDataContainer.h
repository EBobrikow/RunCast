// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Globals.h"
#include "RCListViewDataContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNCAST_API URCListViewDataContainer : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FServerInfo serverInfoData;
	
};
