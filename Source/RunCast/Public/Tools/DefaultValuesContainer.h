// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Globals.h"
#include "DefaultValuesContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RUNCAST_API UDefaultValuesContainer : public UObject
{
	GENERATED_BODY()

public: 

	UDefaultValuesContainer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay Abilities")
	FGameplayAbilitiesValues GameplayAbilitiesValuesContainer;
	
};
