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
}

void ARCCharacter::Multicast_SetAnimState_Implementation(EALSOverlayState overlay)
{
	
	SetOverlayState(overlay);
	AimAction(true);
	//Server_SetRotationMode(rotation, true);
	
	
}

void ARCCharacter::Server_LightAttackAction_Implementation(const bool val)
{
	//LightAttackAction(val);
	if (val && HoldWeaponRef)
	{
		HoldWeaponRef->Server_WeaponFire();
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
	if (WeaponClass /*&& CurrentWeaponClass != WeaponClass*/)
	{
		CurrentWeaponClass = WeaponClass;
		if (ChildActorComponent)
		{
			ChildActorComponent->SetChildActorClass(WeaponClass);

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
	
}

void ARCCharacter::ApplyDamage(float dmg)
{
	UE_LOG(LogTemp, Warning, TEXT("Character take damage %f"), dmg);
	if (HealthComponent)
	{
		HealthComponent->Multicast_DoDamage(dmg);
	}
}

void ARCCharacter::AttackActionBase(bool val)
{
	Server_LightAttackAction(val);
}
