// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/DynamiteBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADynamiteBox::ADynamiteBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

}

void ADynamiteBox::ApplyDamage(float dmg)
{
	BigBadaBum();
}

// Called when the game starts or when spawned
void ADynamiteBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADynamiteBox::BigBadaBum()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* actor : Actors)
	{
		if (actor == this)
		{
			continue;
		}

		FVector lenthVec = actor->GetActorLocation() - GetActorLocation();
		if (lenthVec.Length() <= ExplosionRadius)
		{
			IDamagebleInterface* damageble = Cast<IDamagebleInterface>(actor);
			if (damageble)
			{
				if (lenthVec.Length() > (ExplosionRadius * 0.75f))
				{
					damageble->ApplyDamage(ExplosionDamage * 0.25f);
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.5f))
				{
					damageble->ApplyDamage(ExplosionDamage * 0.5f);
				}
				else if (lenthVec.Length() > (ExplosionRadius * 0.25f))
				{
					damageble->ApplyDamage(ExplosionDamage * 0.75f);
				}
				else
				{
					damageble->ApplyDamage(ExplosionDamage);
				}

				
			}
		}
	}

	ApplyEffects();
	Destroy();
}

// Called every frame
void ADynamiteBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

