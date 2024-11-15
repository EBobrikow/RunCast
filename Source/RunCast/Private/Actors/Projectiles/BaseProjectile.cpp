// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/BaseProjectile.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = BaseSphere;

	BaseSphere->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHitComponent);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ABaseProjectile::SetOwnerCharacter(ACharacter* ownerChar)
{
	OwnerCharacter = ownerChar;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ABaseProjectile::DestroyTimerEnd, DestructionTime, false);
}


void ABaseProjectile::OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ACharacter* otherCharacter = Cast<ACharacter>(OtherActor))
	{
		if (otherCharacter == OwnerCharacter)
		{
			return;
		}
	}

	if (OtherActor == this )
	{
		return;
	}

	UAbilitySystemComponent* ownerAbilityComponent = nullptr;

	if (IAbilitySystemInterface* abilityInterfaceActor = Cast<IAbilitySystemInterface>(OwnerCharacter))
	{
		ownerAbilityComponent = abilityInterfaceActor->GetAbilitySystemComponent();
	}

	UAbilitySystemComponent* targetAbilityComponent = nullptr;
	if (IAbilitySystemInterface* abilityInterfaceActor = Cast<IAbilitySystemInterface>(OtherActor))
	{
		targetAbilityComponent = abilityInterfaceActor->GetAbilitySystemComponent();
	}
		
	
	if (ownerAbilityComponent && targetAbilityComponent && ProjectileDamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = ownerAbilityComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle  NewHandle = ownerAbilityComponent->MakeOutgoingSpec(ProjectileDamageEffect, 1, EffectContext);

		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
				ownerAbilityComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), targetAbilityComponent);
		}

	}
	

	Multicast_AfterEffect();
	PostHit();
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
	Destroy();
}

void ABaseProjectile::Multicast_AfterEffect_Implementation()
{
	ApplyHitAfterEffect();
}



void ABaseProjectile::PostHit()
{
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::DestroyTimerEnd()
{
	if (IsValid(this))
	{
		Destroy();
	}
	
}