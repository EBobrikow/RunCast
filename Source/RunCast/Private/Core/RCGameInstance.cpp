// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameInstance.h"
#include "Kismet/GameplayStatics.h"

void URCGameInstance::StartSoloGame()
{
	bIsSoloGame = true;
	UGameplayStatics::OpenLevel(this,FName("BaseMap"));
}

void URCGameInstance::ExitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

UServerManager* URCGameInstance::GetServerManager()
{
	if (ServerManager == nullptr)
	{
		ServerManager = NewObject<UServerManager>(this);
	}
	return ServerManager;
}

USaveManager* URCGameInstance::GetSaveManager()
{
	if (!SaveManager)
	{
		SaveManager = NewObject<USaveManager>(this);
	}
	return SaveManager;
}



void URCGameInstance::SetCurrentServerInfo(FCurrentServerInfo servInfo)
{
#if UE_SERVER
	CurrentServerInfo = servInfo;
#endif
}
