// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Weapons/RCWeaponPrimary_GA.h"
#include "Actors/Weapons/BaseWeapon.h"

URCWeaponPrimary_GA::URCWeaponPrimary_GA()
{
}

void URCWeaponPrimary_GA::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	CommitAbility(Handle, ActorInfo, ActivationInfo);

	ABaseWeapon* owner = Cast<ABaseWeapon>(ActorInfo->OwnerActor.Get());
	if (owner)
	{
		owner->FireAction();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
