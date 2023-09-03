// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonValue.h"
#include "Globals.generated.h"


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


};



UCLASS()
class RUNCAST_API UGlobals : public UObject
{
	GENERATED_BODY()
	
};
