// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RCDashGameplayAbility.h"
#include "Characters/RCCharacter.h"

URCDashGameplayAbility::URCDashGameplayAbility()
{
	AbilityInputID = ERCAbilityInputID::Dash;
}

void URCDashGameplayAbility::FinishAbilitie()
{
	if (CashedCharacter)
	{
		//CashedCharacter->GetController()->EnableInput(Cast<APlayerController>(CashedCharacter->GetController()));
		if (CashedCharacter->HoldWeaponRef && CashedCharacter->HoldWeaponRef->WeaponSkeletalMesh)
		{
			CashedCharacter->HoldWeaponRef->WeaponSkeletalMesh->SetVisibility(true);
		}
	}
	

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void URCDashGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("[URCDashGameplayAbility::ActivateAbility]"));

	CommitAbility(Handle, ActorInfo, ActivationInfo);
	
	

	ARCCharacter* Character = Cast<ARCCharacter>(ActorInfo->OwnerActor.Get());
	if (Character)
	{
		CashedCharacter = Character;
		FVector velocity = Character->GetVelocity();
		velocity.X = FMath::IsNearlyZero(velocity.X) ? Character->GetActorForwardVector().X : velocity.X;
		velocity.Y = FMath::IsNearlyZero(velocity.Y) ? Character->GetActorForwardVector().Y : velocity.Y;
		velocity.Z = 0;

		velocity.Normalize();
		FVector targetLoc = Character->GetActorLocation() + (velocity * DashDistance);

		
		if (Character->HoldWeaponRef)
		{
			UAbilitySystemComponent* ownerAbilityComponent = Character->HoldWeaponRef->GetAbilitySystemComponent();
			if (ownerAbilityComponent && DashExecutionEffect)
			{
				FGameplayEffectContextHandle EffectContext = ownerAbilityComponent->MakeEffectContext();
				EffectContext.AddSourceObject(this);
				FGameplayEffectSpecHandle  NewHandle = ownerAbilityComponent->MakeOutgoingSpec(DashExecutionEffect, 1, EffectContext);

				if (NewHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
						ownerAbilityComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
				}		

				
			}

			if (Character->HoldWeaponRef->WeaponSkeletalMesh)
			{
				Character->HoldWeaponRef->WeaponSkeletalMesh->SetVisibility(false);
			}
		}
		

		ActivateMotionTask(velocity);


		CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, true);
		return;
		
		
		
	}

	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo,true);
	EndAbility(Handle,ActorInfo, ActivationInfo,true,false);
}
