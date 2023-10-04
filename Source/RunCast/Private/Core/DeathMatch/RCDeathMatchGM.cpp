// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchGM.h"

void ARCDeathMatchGM::BeginPlay()
{
	Super::BeginPlay();
}

TSubclassOf<APawn> ARCDeathMatchGM::GetDefaultCharacterClass() const
{
	return DefaultCharacterClass;
}
