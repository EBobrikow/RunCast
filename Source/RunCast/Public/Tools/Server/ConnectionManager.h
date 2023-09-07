// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IWebSocket.h"
#include "WebSocketsModule.h"
#include "Tools/Server/MessageHandler.h"
#include "Containers/Queue.h"
#include "ConnectionManager.generated.h"




UCLASS()
class RUNCAST_API UConnectionManager : public UObject
{
	GENERATED_BODY()
	
public: 

	UFUNCTION(BlueprintCallable)
	void InitConnection();

	UFUNCTION(BlueprintCallable)
	void CloseConnection();

	UFUNCTION(BlueprintCallable)
	void SendRequest(const FString& msg);

	UFUNCTION(BlueprintCallable)
	void AddRequest(UMessageHandler* RequestObj);

	UFUNCTION(BlueprintCallable)
	void ProceedQueue();

	UFUNCTION(BlueprintCallable)
	bool IsConnected() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString SocketURL = "ws://127.0.0.1:3030";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ServerResponce;

	TSharedPtr<IWebSocket> WebSocketConnection;

	UPROPERTY()
	FOnMessageRecieved OnMessageRecieved;

private:

	
	TQueue<UMessageHandler*> RequestQueue;

	UPROPERTY()
	UMessageHandler* CurrentRequestObject = nullptr;

	UFUNCTION()
	void OnConnected();

	UFUNCTION()
	void OnConnectionError(const FString& error);

	UFUNCTION()
	void OnDisconectionSuccess(const int32& StatusCode, const FString& reason, bool bWasClean);

	UFUNCTION()
	void OnMessageRecieve(const FString& message);
};
