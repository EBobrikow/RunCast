// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/ServerManager.h"

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
	FString name = "Yahoo";
	FString action = "Action: 'ReqestServer',";
	FString param = "ServerName: '" + name + "'";
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
