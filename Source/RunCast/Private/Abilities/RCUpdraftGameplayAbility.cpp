// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RCUpdraftGameplayAbility.h"
#include "Characters/RCCharacter.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"

URCUpdraftGameplayAbility::URCUpdraftGameplayAbility()
{
}

void URCUpdraftGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("[URCUpdraftGameplayAbility::ActivateAbility]"));

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	ARCCharacter* Character = Cast<ARCCharacter>(ActorInfo->OwnerActor.Get());
	if (Character && Character->IsAlive())
	{
		
		FVector targetLoc = Character->GetActorLocation() + (Character->GetActorUpVector() * UpdraftStrength);
		targetLoc.X = 0;
		targetLoc.Y = 0;

		Character->LaunchCharacter(targetLoc,false, true);
	}
	else
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
