// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/RCGameplayAbility.h"
#include "RCUpdraftGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCUpdraftGameplayAbility : public URCGameplayAbility
{
	GENERATED_BODY()

public: 

	URCUpdraftGameplayAbility();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpdraftStrength = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpdraftDuration = 0.5f;
	
};
