// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Server/ServerManager.h"

void UServerManager::InitConnection()
{
	GetConnectionManager()->InitConnection();
}

UConnectionManager* UServerManager::GetConnectionManager()
{
	if (!ConnectionMngr)
	{
		ConnectionMngr = NewObject<UConnectionManager>(this);
	}
	return ConnectionMngr;
}

void UServerManager::ConnectToUEServer(FServerInfo& serverInfo)
{
	ConnectToServer(serverInfo);
}

void UServerManager::RequestNewSessionServer(const FString& serverName)
{
	FString action = "Action: 'ReqestServer',";
	FString param = "ServerName: '" + serverName + "'";
	FString res = "{ " + action + param + " }";

	URequestNewServerHandler* newRequest = NewObject<URequestNewServerHandler>(this);
	newRequest->OnRequestFinished.AddDynamic(this, &UServerManager::RequestNewSessionServerHandle);
	newRequest->SetRequestMessage(res);
	GetConnectionManager()->AddRequest(newRequest);
}

void UServerManager::RequestNewSessionServerHandle(UMessageHandler* newSessionObj)
{
	URequestNewServerHandler* responce = Cast<URequestNewServerHandler>(newSessionObj);
	if (responce) 
	{
		responce->OnRequestFinished.Clear();

		NewServerRequestHandler = responce;
		// Create delay to give server a time to initialize
		GetWorld()->GetTimerManager().SetTimer(ServerStartDelayHandler, this, &UServerManager::ServerStartDelayFinished, 0.01f, false, 5.0f);
	}
}

void UServerManager::RequestSessionsList()
{
	FString action = "Action: 'GetServersList',";
	FString res = "{ " + action + " }";

	UServersListHandler* newRequest = NewObject<UServersListHandler>(this);
	newRequest->OnRequestFinished.AddDynamic(this, &UServerManager::RequestSessionsListHandle);
	newRequest->SetRequestMessage(res);
	GetConnectionManager()->AddRequest(newRequest);

}

void UServerManager::RequestSessionInfoByPort(int32 port)
{
	
	FString action = "Action: 'ReqestServerInfoByPort',";
	FString param = "ServerPort: '" + FString::FromInt(port) + "'";
	FString res = "{ " + action + param + " }";

	UServerInfoByPortHandler* newRequest = NewObject<UServerInfoByPortHandler>(this);
	newRequest->OnRequestFinished.AddDynamic(this, &UServerManager::RequestSessionInfoByPortHandle);
	newRequest->SetRequestMessage(res);
	GetConnectionManager()->AddRequest(newRequest);
}

void UServerManager::HeartBeatSend(FServerInfo& serverInfo)
{
	FString action = "Update: 'HeartBeat',";
	FString param0 = "ServerID: '" + FString::FromInt(serverInfo.Id) + "',";
	FString param = "MatchStatus: '" + FString::FromInt(serverInfo.MatchStatus) + "',";
	FString param1 = "MatchType: '" + serverInfo.MatchType + "',";
	FString param2 = "MapName: '" + serverInfo.MapName + "',";
	FString param3 = "CurrPlayers: '" + FString::FromInt(serverInfo.CurrPlayers) + "',";
	FString param4 = "MaxPlayers: '" + FString::FromInt(serverInfo.MaxPlayers) + "',";
	FString res = "{ " + action + param + param0 + param1 + param2 + param3 + param4 + " }";

	UE_LOG(LogTemp, Log, TEXT("UServerManager::HeartBeatSend Server info \n %s"), *res);

	UHeartBeatHandler* newRequest = NewObject<UHeartBeatHandler>(this);
	newRequest->OnRequestFinished.AddDynamic(this, &UServerManager::HeartBeatRecieve);
	newRequest->SetRequestMessage(res);
	GetConnectionManager()->AddRequest(newRequest);

}

void UServerManager::RequestCloseServer(int32 ServerID)
{
	FString action = "Action: 'StopServerByID',";
	FString param = "ServerID: '" + FString::FromInt(ServerID) + "'";
	FString res = "{ " + action + param + " }";
	UStopServerHandler* newRequest = NewObject<UStopServerHandler>(this);
	newRequest->SetRequestMessage(res);
	GetConnectionManager()->AddRequest(newRequest);
}

void UServerManager::ConnectToMocupServer()
{
	FString res = "open 127.0.0.1";
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), res, UGameplayStatics::GetPlayerController(this, 0));
}

void UServerManager::RequestSessionsListHandle(UMessageHandler* newSessionObj)
{
	UServersListHandler* responce = Cast<UServersListHandler>(newSessionObj);
	if (responce)
	{
		responce->OnRequestFinished.Clear();
		if (OnServerListRecieved.IsBound())
		{
			OnServerListRecieved.Broadcast(responce->serversInfoList);
		}
	}
}

void UServerManager::RequestSessionInfoByPortHandle(UMessageHandler* newSessionObj)
{
	UServerInfoByPortHandler* responce = Cast<UServerInfoByPortHandler>(newSessionObj);
	if (responce)
	{
		if (OnCurrentServerInfoRecieved.IsBound())
		{
			OnCurrentServerInfoRecieved.Broadcast(responce->currentServersInfo);
		}
	}
}

void UServerManager::HeartBeatRecieve(UMessageHandler* newSessionObj)
{
	UHeartBeatHandler* responce = Cast<UHeartBeatHandler>(newSessionObj);
	if (responce)
	{
		responce->OnRequestFinished.Clear();
		if (OnHeartBeatInfoRecieved.IsBound())
		{
			OnHeartBeatInfoRecieved.Broadcast(responce->heartBeatServersInfo);
		}
	}

	
}

void UServerManager::ServerStartDelayFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(ServerStartDelayHandler);
	ConnectToServer(NewServerRequestHandler->serverInfo);
}

void UServerManager::ConnectToServer(FServerInfo& serverInfo)
{
	FString res = "open " + serverInfo.host + ":" + FString::FromInt(serverInfo.Port);
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), res, UGameplayStatics::GetPlayerController(this, 0));
}
