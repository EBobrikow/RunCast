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

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateMotionTask(FVector TargetLocation);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DashMontage;

	UFUNCTION(BlueprintCallable)
	void FinishAbilitie();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> DashExecutionEffect;

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UPROPERTY()
	ARCCharacter* CashedCharacter;
	
};
