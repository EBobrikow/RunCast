// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Dynamite/RCMMC_BoxExplosion.h"
#include "Abilities/RCAttributeSet.h"
#include "Core/RCGameInstance.h"

URCMMC_BoxExplosion::URCMMC_BoxExplosion()
{
	HealthDef.AttributeToCapture = URCAttributeSet::GetHealthAttribute();
	HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HealthDef.bSnapshot = false;

	
}

float URCMMC_BoxExplosion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float ExplosionDamage = 0.0f;
	float ExplosionRadius = 0.0f;
	

	float damageResult = 10.0f;
	FGameplayEffectContextHandle contextHandle = Spec.GetContext();
	if (FGameplayEffectContext* context = contextHandle.Get())
	{
		AActor* effectOwner = context->GetInstigator();
		TArray<TWeakObjectPtr< AActor>> actors = context->GetActors();

		if (URCGameInstance* GI = effectOwner->GetWorld()->GetGameInstance<URCGameInstance>())
		{
			if (UDefaultValuesContainer* valContainer = GI->GetDefaultValuesContaner())
			{
				ExplosionDamage = valContainer->GameplayAbilitiesValuesContainer.DynamiteBoxValues.BoxExplosionDamage;
				ExplosionRadius = valContainer->GameplayAbilitiesValuesContainer.DynamiteBoxValues.BoxExplosionRadius;
			}
		}
	
		if (actors.Num() > 0)
		{
			AActor* target = actors[0].Get();
			
			if (target && effectOwner)
			{
				FVector lenthVec = target->GetActorLocation() - effectOwner->GetActorLocation();
				float distance = lenthVec.Length();
				float mod = 1 - distance / ExplosionRadius;
				damageResult = ExplosionDamage * mod;

			}

			
		}
	}
	

	return damageResult * -1;
}