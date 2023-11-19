// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RCCharacter.h"


ARCCharacter::ARCCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
}

void ARCCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().ClearTimer(DefWeaponSpawnDelay);
	GetWorld()->GetTimerManager().SetTimer(DefWeaponSpawnDelay, this, &ARCCharacter::SpawnDefaultWeapon, 1.0f, false);
}

void ARCCharacter::Multicast_SetAnimState_Implementation(EALSOverlayState overlay)
{
	
	SetOverlayState(overlay);
	AimAction(true);
	//Server_SetRotationMode(EALSRotationMode::Aiming, true);
	
	
}

void ARCCharacter::Server_LightAttackAction_Implementation(const bool val)
{
	//LightAttackAction(val);
	if (HoldWeaponRef)
	{
		HoldWeaponRef->Server_WeaponFire(val);
	}
}


//void ARCCharacter::Multicast_ApplyDamage(const float damage)
//{
//	if (HasAuthority())
//	{
//		ApplyDamage(damage);
//	}
//	
//}

void ARCCharacter::Server_SpawnBaseWeapon_Implementation(TSubclassOf<ABaseWeapon> WeaponClass)
{
	if (WeaponClass)
	{
		CurrentWeaponClass = WeaponClass;
		if (ChildActorComponent && CurrentWeaponClass)
		{
			ChildActorComponent->SetChildActorClass(CurrentWeaponClass);

			if (HeldObjectRoot.Get())
			{
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
				ChildActorComponent->AttachToComponent(HeldObjectRoot.Get(), rules);
			}
			

			HoldWeaponRef = Cast<ABaseWeapon>(ChildActorComponent->GetChildActor());
			if (HoldWeaponRef)
			{
				Multicast_SetAnimState(HoldWeaponRef->WeaponOverlayState);
				HoldWeaponRef->OwnerCharacter = this;
			}

		}


	}
	else
	{
		FString msg = "Invalid weapon class";
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Cyan, *msg);
	}
	
}

void ARCCharacter::ApplyDamageBP(float dmg, ACharacter* damager)
{
	ApplyDamage(dmg, damager);
}

void ARCCharacter::KillCharacter()
{
	if (HasAuthority())
	{
		auto hp = GetHealthComponent();
		if (hp)
		{
			hp->OnActorKilled.Clear();
			hp->OnHealthUpdate.Clear();
		}

		RagdollAction();
	}
	
}



void ARCCharacter::ApplyDamage(float dmg, ACharacter* damager)
{
	UE_LOG(LogTemp, Warning, TEXT("Character take damage %f"), dmg);
	if (HealthComponent)
	{
		HealthComponent->Multicast_DoDamage(dmg, damager);
	}
}

UHealthComponent* ARCCharacter::GetHealthComponent() const
{
	return HealthComponent;
}

void ARCCharacter::SpawnDefaultWeapon()
{
	Server_SpawnBaseWeapon(DefaultWeaponClass);
}

void ARCCharacter::AttackActionBase(bool val)
{
	Server_LightAttackAction(val);
}
