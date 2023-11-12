// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameState.h"
#include "Core/RCGameMode.h"

void ARCGameState::BeginPlay()
{
	Super::BeginPlay();

	/*if (HasAuthority())
	{
		ARCGameMode* GM = Cast<ARCGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->OnMatchBegin.AddDynamic(this, &ARCGameState::MatchStarted);
		}
	}*/
}


