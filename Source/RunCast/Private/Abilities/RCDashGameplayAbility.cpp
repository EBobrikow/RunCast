// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RCDashGameplayAbility.h"
#include "Characters/RCCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"

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

		// apply execution effect to prevent gun fire during dash
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

		FVector selfLoc = Character->GetActorLocation();
		FRotator selfRot = Character->GetActorRotation();
		FVector DeltaToPoint = targetLoc - selfLoc;
		FVector DirToPoint2D = DeltaToPoint.GetSafeNormal2D();
		FVector LocalDirToPoint2D = selfRot.UnrotateVector(DirToPoint2D);
		float AngleToPoint = FMath::Sign(LocalDirToPoint2D.Y) * FMath::Acos(LocalDirToPoint2D.X);
		// left -1.57 right 1.57 forward 0 back 3.14\ -3.14
		UAnimMontage* montageToPlay = DashForwardMontage;
		float angleVal = FMath::Abs(AngleToPoint);
		if (angleVal > 0.753f && angleVal < 2.3f)
		{
			montageToPlay = AngleToPoint > 0.0f ? DashRightMontage : DashLeftMontage;
		}
		else if (angleVal > 2.3f)
		{
			montageToPlay = DashBackwardMontage;
		}

		UAbilityTask_PlayMontageAndWait* montageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, montageToPlay);
		montageTask->OnCompleted.AddDynamic(this, &URCDashGameplayAbility::FinishAbilitie);
		montageTask->ReadyForActivation();

		UAbilityTask_ApplyRootMotionConstantForce* forceMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, NAME_None,
			velocity, DashStrength, DashDuration,false,nullptr,ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity,FVector(),0.0f, false);
		forceMotionTask->ReadyForActivation();

		
		return;		
	}

	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo,true);
	EndAbility(Handle,ActorInfo, ActivationInfo,true,false);
}
