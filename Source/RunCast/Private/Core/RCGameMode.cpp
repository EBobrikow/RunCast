// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameMode.h"
#include "Core/RCPlayerController.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void ARCGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ARCGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (OnPlayerLogin.IsBound())
	{
		OnPlayerLogin.Broadcast(NewPlayer);
	}

	URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->ConnectedPlayersNum++;
	}
	
}

void ARCGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (OnPlayerLogout.IsBound())
	{
		OnPlayerLogout.Broadcast(Exiting);
	}

	URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->ConnectedPlayersNum--;
		if (GameInstance->ConnectedPlayersNum == 0)
		{
			FServerInfo info = GameInstance->GetRemoteServerInfo();
			if (info.Id != -1)
			{
				GameInstance->GetServerManager()->RequestCloseServer(info.Id);
#if UE_SERVER
				FGenericPlatformMisc::RequestExit(false);
#endif
			}
			
		}
	}
}
