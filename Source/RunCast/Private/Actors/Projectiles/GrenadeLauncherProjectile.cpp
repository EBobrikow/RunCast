// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/GrenadeLauncherProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/DamagebleInterface.h"

void AGrenadeLauncherProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenadeLauncherProjectile::ApplyExplosionDamage()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* actor : Actors)
	{
		FVector lenthVec = actor->GetActorLocation() - GetActorLocation();
		if (lenthVec.Length() <= ExplosionRadius)
		{
			IDamagebleInterface* damageble = Cast<IDamagebleInterface>(actor);
			if (damageble)
			{
				if (lenthVec.Length() > (ExplosionRadius * 0.75f))
				{
					 damageble->ApplyDamage(ExplosionDamage * 0.25f, OwnerCharacter);
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.5f))
				{
					damageble->ApplyDamage(ExplosionDamage * 0.5f, OwnerCharacter);
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.25f))
				{
					damageble->ApplyDamage(ExplosionDamage * 0.75f, OwnerCharacter);
				}
			}
		}
	}
}
