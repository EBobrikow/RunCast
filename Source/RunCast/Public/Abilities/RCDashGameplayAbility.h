// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/RCGameplayAbility.h"
#include "RCDashGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCDashGameplayAbility : public URCGameplayAbility
{
	GENERATED_BODY()

public: 

	URCDashGameplayAbility();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DashVelocityMultiplier = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DashDistance = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DashStrength = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DashDuration = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DashForwardMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DashLeftMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DashRightMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DashBackwardMontage;

	UFUNCTION(BlueprintCallable)
	void FinishAbilitie();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> DashExecutionEffect;

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UPROPERTY()
	class ARCCharacter* CashedCharacter;
	
};
