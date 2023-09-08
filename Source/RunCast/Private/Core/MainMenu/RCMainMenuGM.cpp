// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainMenu/RCMainMenuGM.h"

void ARCMainMenuGM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GameInstance)
	{
		GameInstance->ShowMainMenu();
	}
	
}
