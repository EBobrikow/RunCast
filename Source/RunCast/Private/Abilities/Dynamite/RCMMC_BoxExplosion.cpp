// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Dynamite/RCMMC_BoxExplosion.h"
#include "Abilities/RCAttributeSet.h"

URCMMC_BoxExplosion::URCMMC_BoxExplosion()
{
	HealthDef.AttributeToCapture = URCAttributeSet::GetHealthAttribute();
	HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HealthDef.bSnapshot = false;

	
}

float URCMMC_BoxExplosion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float damageResult = 10.0f;
	FGameplayEffectContextHandle contextHandle = Spec.GetContext();
	if (FGameplayEffectContext* context = contextHandle.Get())
	{
		AActor* effectOwner = context->GetInstigator();
		TArray<TWeakObjectPtr< AActor>> actors = context->GetActors();
	
		if (actors.Num() > 0)
		{
			AActor* target = actors[0].Get();
			
			if (target && effectOwner)
			{
				FVector lenthVec = target->GetActorLocation() - effectOwner->GetActorLocation();
				if (lenthVec.Length() > (ExplosionRadius * 0.75f))
				{
					damageResult = ExplosionDamage * 0.25f;
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.5f))
				{
					damageResult = ExplosionDamage * 0.5f;
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.25f))
				{
					damageResult = ExplosionDamage * 0.75f;
				}
				else
				{
					damageResult = ExplosionDamage ;
				}

				UE_LOG(LogTemp, Warning, TEXT("[CalculateBaseMagnitude] Target = %s, Source = %s, distance = %f, DamageResult = %f"), *target->GetName(), *effectOwner->GetName(), lenthVec.Length(), damageResult * -1);
			}

			
		}
	}
	

	return damageResult * -1;
}