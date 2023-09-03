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

void UServerManager::RequestNewSessionServer(const FString& serverName)
{
	FString name = "Yahoo";
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

		FString res = "open " + responce->serverInfo.host + ":" + FString::FromInt(responce->serverInfo.Port);
		UGameplayStatics::OpenLevel(this, FName(res));
	}
}
