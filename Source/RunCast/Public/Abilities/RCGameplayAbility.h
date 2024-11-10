// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Tools/Globals.h"
#include "RCGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public: 

	URCGameplayAbility();

	UPROPERTY(EditAnywhere)
	ERCAbilityInputID AbilityInputID{ ERCAbilityInputID::None };


};
