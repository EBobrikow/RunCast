// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/Server/ConnectionManager.h"
#include "Tools/Server/MessageHandler.h"
//#include "Tools/Globals.h"
#include "Kismet/GameplayStatics.h"
#include "ServerManager.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerListRecieved, TArray<FServerInfo>, serversList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentServerInfoRecieved, FCurrentServerInfo, currentServInfo);

UCLASS()
class RUNCAST_API UServerManager : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitConnection();

	UFUNCTION(BlueprintCallable)
	UConnectionManager* GetConnectionManager();

	UFUNCTION(BlueprintCallable)
	void ConnectToUEServer(FServerInfo& serverInfo);

	UFUNCTION(BlueprintCallable)
	void RequestNewSessionServer(const FString& serverName);

	UFUNCTION(BlueprintCallable)
	void RequestSessionsList();

	UFUNCTION(BlueprintCallable)
	void RequestSessionInfoByPort(int32 port);

	UPROPERTY()
	FOnServerListRecieved OnServerListRecieved;

	UPROPERTY()
	FOnCurrentServerInfoRecieved OnCurrentServerInfoRecieved;

#if UE_SERVER

#endif

protected: 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UConnectionManager* ConnectionMngr = nullptr;

	UFUNCTION()
	void RequestNewSessionServerHandle(UMessageHandler* newSessionObj);

	UFUNCTION()
	void RequestSessionsListHandle(UMessageHandler* newSessionObj);

	UFUNCTION()
	void RequestSessionInfoByPortHandle(UMessageHandler* newSessionObj);

private: 

	UPROPERTY()
	FTimerHandle ServerStartDelayHandler;

	UPROPERTY()
	URequestNewServerHandler* NewServerRequestHandler;

	UFUNCTION()
	void ServerStartDelayFinished();

	UFUNCTION()
	void ConnectToServer(FServerInfo& serverInfo);

};
