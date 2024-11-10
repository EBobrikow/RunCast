// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/RCGameplayAbility.h"
#include "RCWeaponPrimary_GA.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCWeaponPrimary_GA : public URCGameplayAbility
{
	GENERATED_BODY()

public:

	URCWeaponPrimary_GA();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
};
