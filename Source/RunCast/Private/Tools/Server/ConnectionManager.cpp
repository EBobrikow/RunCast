// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Server/ConnectionManager.h"
#include "Modules/ModuleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonValue.h"


void UConnectionManager::InitConnection()
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}
	ReadConfigFile();
	WebSocketConnection = FWebSocketsModule::Get().CreateWebSocket(SocketURL);

	WebSocketConnection->OnConnected().AddUFunction(this, FName("OnConnected"));
	WebSocketConnection->OnConnectionError().AddUFunction(this, FName("OnConnectionError"));
	WebSocketConnection->OnClosed().AddUFunction(this, FName("OnDisconectionSuccess"));
	WebSocketConnection->OnMessage().AddUFunction(this, FName("OnMessageRecieve"));
	

	WebSocketConnection->Connect();
	CurrentRequestObject = nullptr;
}

void UConnectionManager::CloseConnection()
{
	if (WebSocketConnection && WebSocketConnection->IsConnected())
	{
		WebSocketConnection->Close(1000, TEXT("Client exit game"));
	}
	
}



void UConnectionManager::SendRequest(const FString& msg)
{
	if (WebSocketConnection && WebSocketConnection->IsConnected())
	{
		WebSocketConnection->Send(msg);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UConnectionManager::SendRequest invalid WebSocketConnection or socket not connected!"));
	}
}

void UConnectionManager::AddRequest(UMessageHandler* RequestObj)
{
	RequestQueue.Enqueue(RequestObj);
	if (CurrentRequestObject == nullptr)
	{
		ProceedQueue();
	}
}

void UConnectionManager::ProceedQueue()
{
	if (CurrentRequestObject != nullptr || RequestQueue.IsEmpty())
	{
		return;
	}
	else
	{
		UMessageHandler* requestItem = nullptr;
		if (RequestQueue.Dequeue(requestItem))
		{
			CurrentRequestObject = requestItem;
			//CurrentRequestObject->AddCallback(OnMessageRecieved);
			OnMessageRecieved.AddDynamic(requestItem, &UMessageHandler::OnURecieved);
			SendRequest(CurrentRequestObject->GetRequestMessage());
		}
	}
}

bool UConnectionManager::IsConnected() const
{
	if (WebSocketConnection)
	{
		return WebSocketConnection->IsConnected();
	}
	return false;
}



void UConnectionManager::OnConnected()
{
	UE_LOG(LogTemp, Warning, TEXT("Client: Connected"));
}

void UConnectionManager::OnConnectionError(const FString& error)
{
	UE_LOG(LogTemp, Error, TEXT("Connection Error: %s"), *error);
}

void UConnectionManager::OnDisconectionSuccess(const int32& StatusCode, const FString& reason, bool bWasClean)
{
	UE_LOG(LogTemp, Warning, TEXT("Disconnection: \n Reason: %s \n Status code: %i"), *reason ,StatusCode);
}

void UConnectionManager::OnMessageRecieve(const FString& message)
{
	UE_LOG(LogTemp, Warning, TEXT("Server msg: %s"), *message);
	if (OnMessageRecieved.IsBound())
	{
		OnMessageRecieved.Broadcast(message);
		OnMessageRecieved.RemoveDynamic(CurrentRequestObject, &UMessageHandler::OnRecieved);
	}
	
	CurrentRequestObject = nullptr;

	ProceedQueue();
}

void UConnectionManager::ReadConfigFile()
{
	FString path = FPaths::ConvertRelativePathToFull(FPaths::LaunchDir()) + ConfigFileName;

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
	{
		FString readRes = ""; 
		if (FFileHelper::LoadFileToString(readRes, *path))
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(readRes);
			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				FString adress = "";
				int32 port = -1;
				for (auto val : JsonObject->Values)
				{
					if (val.Key == ServerManagerUrl && !val.Value->IsNull())
					{
						adress = val.Value->AsString(); 
						
					}
					else if (val.Key == Port && !val.Value->IsNull())
					{
						port = val.Value->AsNumber();
					}
				}

				SocketURL = "ws://" + adress + ":" + FString::FromInt(port);
			}
		}
	}
}

