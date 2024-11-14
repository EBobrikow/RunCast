// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Weapons/RCMMC_LauncherGrenadeExplosion.h"
#include "Core/RCGameInstance.h"

URCMMC_LauncherGrenadeExplosion::URCMMC_LauncherGrenadeExplosion()
{
}

float URCMMC_LauncherGrenadeExplosion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float ExplosionDamage = 0.0f;
	float ExplosionRadius = 0.0f;
	float damageResult = 30.0f;
	FGameplayEffectContextHandle contextHandle = Spec.GetContext();
	if (FGameplayEffectContext* context = contextHandle.Get())
	{
		AActor* effectOwner = Cast<AActor>(context->GetSourceObject());
		TArray<TWeakObjectPtr< AActor>> actors = context->GetActors();

		

		if (URCGameInstance* GI = effectOwner->GetWorld()->GetGameInstance<URCGameInstance>())
		{
			if (UDefaultValuesContainer* valContainer = GI->GetDefaultValuesContaner())
			{
				ExplosionDamage = valContainer->GameplayAbilitiesValuesContainer.LauncherGrenadeValues.GrenadeExplosionDamage;
				ExplosionRadius = valContainer->GameplayAbilitiesValuesContainer.LauncherGrenadeValues.GrenadeExplosionRadius;
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
