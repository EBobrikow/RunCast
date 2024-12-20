// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonValue.h"
#include "Engine/Texture.h"
#include "Engine/Texture2D.h"
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
		static const FString MatchType = TEXT("matchType");
		static const FString MapName = TEXT("mapName");
		static const FString CurrPlayers = TEXT("currentPlayers");
		static const FString MaxPlayers = TEXT("maxPlayers");
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

	UPROPERTY(BlueprintReadWrite)
	FString MatchType;

	UPROPERTY(BlueprintReadWrite)
	FString MapName;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrPlayers;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxPlayers;


	FServerInfo();

	FServerInfo(
		int32 _id,
		const FString& _serverName,
		int32 _port,
		const FString& _host,
		int32 _matchStatus,
		const FString& _matchType,
		const FString& _mapName,
		int32 _currPlayers,
		int32 maxPlayers
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* MapPreviewImage;

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

UENUM(BlueprintType)
enum class ELobbyPlayerAuthority : uint8
{
	None,
	GameMaster,
	ConnectedPlayer,
	AIBot
};

UENUM(BlueprintType)
enum class ELobbyPlayerReady : uint8
{
	None,
	Ready,
	Idle,
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ELobbyPlayerAuthority> PlayerAuthority;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ELobbyPlayerReady> PlayerReady;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UClass* SelectedCharacterClass;

	FPlayerData();

	FPlayerData(FString name, ELobbyPlayerAuthority authority, ELobbyPlayerReady isReady, UClass* characterClass);

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
	FString MatchGameModePath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DefaultMaxPlayers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* MatchPreviewImage;

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


USTRUCT(BlueprintType)
struct FScoreBoardData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 KillCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DeathCount;

	FScoreBoardData();

	FScoreBoardData(const FString& _name, int32 kills, int32 death);
};

UENUM(BlueprintType)
enum class ESettingsQuality : uint8
{
	Low,
	Medium,
	High,
	Ultra
};


UCLASS()
class RUNCAST_API UGlobals : public UObject
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class ERCAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Dash,
	Updraft,
	PrimaryWeaponFire
};

USTRUCT(BlueprintType)
struct FDynamiteBoxAbilitiesValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float BoxExplosionRadius;

	UPROPERTY(EditAnywhere)
	float BoxExplosionDamage;

};

USTRUCT(BlueprintType)
struct FLauncherGrenadeValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float GrenadeExplosionRadius;

	UPROPERTY(EditAnywhere)
	float GrenadeExplosionDamage;

};

USTRUCT(BlueprintType)
struct FGameplayAbilitiesValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FDynamiteBoxAbilitiesValues DynamiteBoxValues;

	UPROPERTY(EditAnywhere)
	FLauncherGrenadeValues LauncherGrenadeValues;
};

UENUM(BlueprintType)
enum class EWeaponIconType : uint8
{
	None,
	Pistol,
	Riffle,
	Launcher,
	Dynamite
};