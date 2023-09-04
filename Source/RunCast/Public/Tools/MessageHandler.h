// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonValue.h"
#include "Tools/Globals.h"
//#include "Tools/ConnectionManager.h"
#include "MessageHandler.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestFinished, UMessageHandler*, requestObj);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageRecieved, FString, message);

UCLASS()
class RUNCAST_API UMessageHandler : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnURecieved(FString message);

	virtual void OnRecieved(FString message);

	virtual const FString& GetRequestMessage() const;

	virtual void SetRequestMessage(const FString& message);

	virtual void RequestAction();
	
	UPROPERTY()
	FOnRequestFinished OnRequestFinished;

	//virtual void AddCallback(FOnMessageRecieved& callback);

protected:

	//UPROPERTY()
	//FOnMessageRecieved OnMessageRecievedCallback;

	UPROPERTY()
	FString requestMessage;

	void virtual ParseJsonObject(TSharedPtr<FJsonObject> JsonObj);

	bool parseAsString(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, FString& value);
	bool parseAsNumber(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, int32& value);
	bool parseAsNumber(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, double& value);
	bool parseAsBool(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, bool& value);


};


UCLASS()
class RUNCAST_API URequestNewServerHandler : public UMessageHandler
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FServerInfo serverInfo;

protected:

	void virtual ParseJsonObject(TSharedPtr<FJsonObject> JsonObj) override;
};

UCLASS()
class RUNCAST_API UServersListHandler : public UMessageHandler
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FServerInfo> serversInfoList;

protected:

	void virtual ParseJsonObject(TSharedPtr<FJsonObject> JsonObj) override;
};