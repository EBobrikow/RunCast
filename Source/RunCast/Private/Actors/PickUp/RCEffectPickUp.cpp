// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUp/RCEffectPickUp.h"
#include "AbilitySystemInterface.h"
#include "Components/RCAbilitySystemComponent.h"

ARCEffectPickUp::ARCEffectPickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	USceneComponent* defRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defRoot"));
	RootComponent = defRoot;


	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	BaseSphere->SetupAttachment(RootComponent);
	if (BaseSphere)
	{
		BaseSphere->SetSphereRadius(100.0f);
		BaseSphere->OnComponentBeginOverlap.AddDynamic(this, &ARCEffectPickUp::OnBeginOverlap);
	}
}

void ARCEffectPickUp::BeginPlay()
{
	Super::BeginPlay();
}

void ARCEffectPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	if (IAbilitySystemInterface* target = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* targetAbilityComponent = target->GetAbilitySystemComponent();		
		if (targetAbilityComponent && ApplyedEffect)
		{
			ResetOverlap();
			FGameplayEffectContextHandle EffectContext = targetAbilityComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle  NewHandle = targetAbilityComponent->MakeOutgoingSpec(ApplyedEffect, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
					targetAbilityComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get()); //ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), targetAbilityComponent);
			}
			//Char->Server_SpawnBaseWeapon(WeaponClass);
			if (OnPickupDelegate.IsBound())
			{
				OnPickupDelegate.Broadcast();
			}
		}
	}
	
}

void ARCEffectPickUp::ResetOverlap()
{
	if (BaseSphere)
	{
		BaseSphere->OnComponentBeginOverlap.Clear();
	}
}
