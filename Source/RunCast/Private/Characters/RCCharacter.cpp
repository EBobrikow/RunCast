// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RCCharacter.h"


ARCCharacter::ARCCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	
}

void ARCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARCCharacter::SetAttackAlpha(float alpha)
{
	SetAttackBlendAlpha(alpha);
}

void ARCCharacter::ApplyDamage(float dmg)
{
	UE_LOG(LogTemp, Warning, TEXT("Character take damage %f"), dmg);
}
