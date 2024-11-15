// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/GrenadeLauncherProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemInterface.h"
#include "Components/RCAbilitySystemComponent.h"
#include "Abilities/RCAttributeSet.h"
#include "GameplayEffect.h"
#include "Characters/RCCharacter.h"
#include "Actors/Weapons/DynamiteBox.h"

void AGrenadeLauncherProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenadeLauncherProjectile::ApplyExplosionDamage()
{
	TArray<AActor*> BoxActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADynamiteBox::StaticClass(), BoxActors);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARCCharacter::StaticClass(), Actors);
	for (AActor* box : BoxActors)
	{
		Actors.Add(box);
	}


	for (AActor* actor : Actors)
	{
		FVector lenthVec = actor->GetActorLocation() - GetActorLocation();
		if (lenthVec.Length() <= ExplosionRadius)
		{
			IAbilitySystemInterface* target = Cast<IAbilitySystemInterface>(actor);
			if (target && OwnerCharacter && (actor != OwnerCharacter))
			{

				UAbilitySystemComponent* ownerAbilityComponent = Cast<IAbilitySystemInterface>(OwnerCharacter)->GetAbilitySystemComponent();
				UAbilitySystemComponent* targetAbilityComponent = target->GetAbilitySystemComponent();



				if (ownerAbilityComponent && targetAbilityComponent && GrenadeExplosionEffect)
				{
					FGameplayEffectContextHandle EffectContext = ownerAbilityComponent->MakeEffectContext();
					EffectContext.AddSourceObject(this);
					TArray<TWeakObjectPtr<AActor>> actors;
					TWeakObjectPtr<AActor> actorObj = Cast<AActor>(target);
					actors.Add(actorObj);
					EffectContext.AddActors(actors);

					FGameplayEffectSpecHandle  NewHandle = ownerAbilityComponent->MakeOutgoingSpec(GrenadeExplosionEffect, 1, EffectContext);

					if (NewHandle.IsValid())
					{
						FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
							ownerAbilityComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), targetAbilityComponent);
					}

				}
			}
		
		}
	}
}

void AGrenadeLauncherProjectile::PostHit()
{
	if (HasAuthority())
	{
		ApplyExplosionDamage();
	}
	
}
