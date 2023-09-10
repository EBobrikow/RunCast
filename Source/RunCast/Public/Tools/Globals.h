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

USTRUCT(BlueprintType, Blueprintable)
struct FArenaMapData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapPath;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UImage* MapPreviewImage;*/

};




UENUM(BlueprintType)
enum class ELobbyState : uint8
{
	Entrance,
	DeathMatchLobby,
};

UENUM(BlueprintType)
enum class EMatchType : uint8
{
	TeamFight,
	DeathMatch,
	CaptureFlag,
};


USTRUCT(BlueprintType, Blueprintable)
struct FArenaMatchData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EMatchType> MatchType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MatchName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DefaultMaxPlayers;

};


USTRUCT(BlueprintType, Blueprintable)
struct FCurrentServerInfo
{
	GENERATED_BODY()

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ServerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 OwnPort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ServerID;

};

UCLASS()
class RUNCAST_API UGlobals : public UObject
{
	GENERATED_BODY()
	
};
