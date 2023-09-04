// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonValue.h"
#include "Globals.generated.h"


namespace JSVal
{
	namespace ServerInfo
	{
		static const FString Id = TEXT("Id");
		static const FString ServerName = TEXT("serverName");
		static const FString Port = TEXT("port");
		static const FString Host = TEXT("host");
		static const FString MatchStatus = TEXT("matchStatus");
	}
}

USTRUCT(BlueprintType)
struct FServerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Id;

	UPROPERTY(BlueprintReadWrite)
	FString ServerName;

	UPROPERTY(BlueprintReadWrite)
	int32 Port;

	UPROPERTY(BlueprintReadWrite)
	FString host;

	UPROPERTY(BlueprintReadWrite)
	int32 MatchStatus;

	FServerInfo();

	FServerInfo(
		int32 _id,
		const FString& _serverName,
		int32 _port,
		const FString& _host,
		int32 _matchStatus
	);

};



UCLASS()
class RUNCAST_API UGlobals : public UObject
{
	GENERATED_BODY()
	
};
