// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyGM.h"

void ARCLobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	

#if UE_SERVER
	GetServerInfoWhenReady();
	if (GameInstance)
	{
		GameInstance->StartHeartBeat(this);
	}	
#endif
}

ELobbyState ARCLobbyGM::GetDefaultLobbyState() const
{
	return DefaultLobbyState;
}


TArray<FArenaMatchData> ARCLobbyGM::GetMatchesData() const
{
	return MatchDataList;
}

TArray<FArenaMapData> ARCLobbyGM::GetArenasData() const
{
	return ArenaDataList;
}

void ARCLobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ARCPlayerController* PC = Cast<ARCPlayerController>(NewPlayer);
	if (PC)
	{
		if (GameInstance->ConnectedPlayersNum == 1)
		{
			FPlayerData pData = PC->GetPlayerData();
			pData.PlayerAuthority = ELobbyPlayerAuthority::GameMaster;
			PC->Server_SetPlayerData(pData);
			//PC->Client_PreservePlayerData();
		}
		else
		{
			FPlayerData pData = PC->GetPlayerData();
			pData.PlayerAuthority = ELobbyPlayerAuthority::ConnectedPlayer;
			PC->Server_SetPlayerData(pData);
			//PC->Client_PreservePlayerData();
		}
	}

	if (GameInstance)
	{
		FServerInfo servInfo = GameInstance->GetRemoteServerInfo();
		if (servInfo.Id != -1)
		{
			servInfo.CurrPlayers = GameInstance->ConnectedPlayersNum;
			GameInstance->SetCurrentServerInfo(servInfo);
		}
		
	}

	if (OnLobbyPlayerLogin.IsBound())
	{
		OnLobbyPlayerLogin.Broadcast(NewPlayer);
	}

}

void ARCLobbyGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	bool bIsGameMasterExist = false;
	if (GameInstance)
	{
		if (GameInstance->ConnectedPlayersNum > 0)
		{
			for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
				if (Controller)
				{
					FPlayerData pData = Controller->GetPlayerData();
					if (pData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
					{
						bIsGameMasterExist = true;
						break;
					}
				}
			}

			if (!bIsGameMasterExist)
			{
				for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					ARCPlayerController* Controller = Cast<ARCPlayerController>(Iterator->Get());
					if (Controller)
					{
						FPlayerData pData = Controller->GetPlayerData();
						pData.PlayerAuthority = ELobbyPlayerAuthority::GameMaster;
						Controller->Server_SetPlayerData(pData);
						//Controller->Client_PreservePlayerData();
						break;
					}
				}
			}
		}

		FServerInfo servInfo = GameInstance->GetRemoteServerInfo();
		if (servInfo.Id != -1)
		{
			servInfo.CurrPlayers = GameInstance->ConnectedPlayersNum;
			GameInstance->SetCurrentServerInfo(servInfo);
		}

	}


	if (OnLobbyPlayerLogout.IsBound())
	{
		OnLobbyPlayerLogout.Broadcast(Exiting);
	}
	
}





void ARCLobbyGM::FillCurrentServerInfoRequest()
{
	if (GameInstance)
	{
		int32 port = GetWorld()->URL.Port;
		GameInstance->GetServerManager()->OnCurrentServerInfoRecieved.AddDynamic(this, &ARCLobbyGM::CurrentServerInfoRequestHandle);
		GameInstance->GetServerManager()->RequestSessionInfoByPort(port);
	}
	
}

void ARCLobbyGM::CurrentServerInfoRequestHandle(FServerInfo servInfo)
{
	if (GameInstance)
	{
		GameInstance->GetServerManager()->OnCurrentServerInfoRecieved.Clear();
		GameInstance->SetCurrentServerInfo(servInfo);
	}
}

void ARCLobbyGM::GetServerInfoWhenReady()
{
	if (GameInstance)
	{
		if (!GameInstance->GetServerManager()->GetConnectionManager()->IsConnected())
		{
			GetWorld()->GetTimerManager().ClearTimer(InfoReuestTimer);
			GetWorld()->GetTimerManager().SetTimer(InfoReuestTimer, this, &ARCLobbyGM::GetServerInfoWhenReady, 0.01f, false, 0.5f);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(InfoReuestTimer);
			FillCurrentServerInfoRequest();
		}
	}
}
