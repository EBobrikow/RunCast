// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Tools/Globals.h"
#include "Net/UnrealNetwork.h"
#include "RCGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreBoardUpdate, TArray<FScoreBoardData>, scoreTable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowFinaleStat, TArray<FScoreBoardData>, scoreTable);

UCLASS()
class RUNCAST_API ARCGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY()
	FOnScoreBoardUpdate OnScoreBoardUpdate;

	UPROPERTY()
	FOnShowFinaleStat OnShowFinaleStat;

	UFUNCTION(Server, Reliable)
	void Server_UpdateScoreBoard();

protected: 

	UPROPERTY()
	TArray<FScoreBoardData> ScoreBoardTable;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnScoreUpdated(const TArray<FScoreBoardData>& scoreList);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FinaleScoreData(const TArray<FScoreBoardData>& scoreList);

	UFUNCTION()
	void SortScoreBoard();

	UFUNCTION()
	void UpdateScoreBoard();

	UFUNCTION()
	void OnMatchEnd();



};
