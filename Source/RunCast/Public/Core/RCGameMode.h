// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Core/RCGameInstance.h"
#include "RCGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLogin, APlayerController*, playerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLogout, AController*, exitController);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimeUpdate, int32, Minutes, int32, Seconds);

UCLASS()
class RUNCAST_API ARCGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY()
	FOnPlayerLogin OnPlayerLogin;

	UPROPERTY()
	FOnPlayerLogout OnPlayerLogout;

	UPROPERTY()
	FOnMatchBegin OnMatchBegin;

	UPROPERTY()
	FOnMatchEnd OnMatchEnd;

	UPROPERTY()
	FOnTimeUpdate OnTimeUpdate;

	UFUNCTION(BlueprintCallable)
	float GetMatchDuration();

	UFUNCTION(BlueprintCallable)
	void StartMatchDelay();

	UFUNCTION()
	void GetCurrentMatchTime(int32& Min, int32& Sec);

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Match time config")
	int32 MatchDuration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Match time config")
	float StartDelay;

	UPROPERTY()
	int32 CurrentMinutes;

	UPROPERTY()
	int32 CurrentSeconds;

	UFUNCTION()
	void MatchStart();

	UFUNCTION()
	void TimeCount();


private: 

	UPROPERTY()
	FTimerHandle StartDelayTimer;

	UPROPERTY()
	FTimerHandle TimeCountTimer;
};
