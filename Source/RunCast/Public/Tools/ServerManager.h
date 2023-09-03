// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/ConnectionManager.h"
#include "Tools/MessageHandler.h"
#include "Kismet/GameplayStatics.h"
#include "ServerManager.generated.h"

/**
 * 
 */
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
	void RequestNewSessionServer(const FString& serverName);

protected: 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UConnectionManager* ConnectionMngr = nullptr;

	UFUNCTION()
	void RequestNewSessionServerHandle(UMessageHandler* newSessionObj);

};
