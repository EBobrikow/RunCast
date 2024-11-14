// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/DynamiteBox.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/RCCharacter.h"
#include "Core/RCGameInstance.h"

// Sets default values
ADynamiteBox::ADynamiteBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SetReplicates(true);

	AbilitySystemComponent = CreateDefaultSubobject<URCAbilitySystemComponent>(TEXT("AbilityComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URCAttributeSet>(TEXT("Attributes"));

}

void ADynamiteBox::ApplyDamage(float dmg, ACharacter* damager)
{
	Server_TakeDamage();
	//BigBadaBum();
}

void ADynamiteBox::ApplyAbilityDamage(ACharacter* instigatorCharacter)
{

	Server_TakeDamage();
}

UAbilitySystemComponent* ADynamiteBox::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ADynamiteBox::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (Attributes)
		{
			Attributes->OnCharacterKilled.AddDynamic(this, &ADynamiteBox::ApplyAbilityDamage);
		}

		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(this, this);
			AddStartupGameplayAbilities();
		}
	}

	if (URCGameInstance* GI = GetWorld()->GetGameInstance<URCGameInstance>())
	{
		if (const UDefaultValuesContainer* valContainer = GI->GetDefaultValuesContaner())
		{
			ExplosionDamage = valContainer->GameplayAbilitiesValuesContainer.DynamiteBoxValues.BoxExplosionDamage;
			ExplosionRadius = valContainer->GameplayAbilitiesValuesContainer.DynamiteBoxValues.BoxExplosionRadius;
		}
	}

}

void ADynamiteBox::BigBadaBum()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARCCharacter::StaticClass(), Actors);
	for (AActor* actor : Actors)
	{
		if (actor == this)
		{
			continue;
		}

		if (actor->GetClass() == this->GetClass())
		{
			continue;
		}

		FVector lenthVec = actor->GetActorLocation() - GetActorLocation();
		if (lenthVec.Length() <= ExplosionRadius)
		{
			IAbilitySystemInterface* target = Cast<IAbilitySystemInterface>(actor);
			if (target)
			{

				UAbilitySystemComponent* ownerAbilityComponent = GetAbilitySystemComponent();
				UAbilitySystemComponent* targetAbilityComponent = target->GetAbilitySystemComponent();
				


				if (ownerAbilityComponent && targetAbilityComponent && ExplosionDamageEffect)
				{
					FGameplayEffectContextHandle EffectContext = ownerAbilityComponent->MakeEffectContext();
					EffectContext.AddSourceObject(this);
					TArray<TWeakObjectPtr<AActor>> actors;
					TWeakObjectPtr<AActor> actorObj = Cast<AActor>(target);
					actors.Add(actorObj);
					EffectContext.AddActors(actors);

					FGameplayEffectSpecHandle  NewHandle = ownerAbilityComponent->MakeOutgoingSpec(ExplosionDamageEffect, 1, EffectContext);

					if (NewHandle.IsValid())
					{
						FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
							ownerAbilityComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), targetAbilityComponent);
					}

				}
			}
		}
	}
	Multicast_AfterEffect();
	Destroy();
}

void ADynamiteBox::Server_TakeDamage_Implementation()
{
	BigBadaBum();
}

void ADynamiteBox::Multicast_AfterEffect_Implementation()
{
	ApplyEffects();
}

void ADynamiteBox::AddStartupGameplayAbilities()
{
	if (AbilitySystemComponent)
	{
		if (GetLocalRole() == ROLE_Authority && !AbilityInitialized)
		{
			

			for (TSubclassOf<UGameplayEffect>& effect : PassiveGameplayEffects)
			{
				FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
				EffectContext.AddSourceObject(this);

				FGameplayEffectSpecHandle  NewHandle = AbilitySystemComponent->MakeOutgoingSpec(effect, 1, EffectContext);

				if (NewHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
						AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
				}
			}
			AbilityInitialized = true;
		}

	}
}

// Called every frame
void ADynamiteBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

