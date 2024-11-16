// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/ALSAIController.h"
#include "Tools/Globals.h"
#include "Interfaces/ScoreBoardInterface.h"
#include "RCAIController.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCAIController : public AALSAIController, public IScoreBoardInterface
{
	GENERATED_BODY()
	
public: 
	ARCAIController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void Init(FPlayerData playerData);


protected: 

	UFUNCTION()
	void CreateCharacter();

	UFUNCTION()
	void CharacterKilled(AActor* killer);


	UFUNCTION()
	void Restart();

	UFUNCTION()
	void MatchEnd();

	UPROPERTY()
	FPlayerData PlayerData;

	UPROPERTY()
	float RestartDelayTime = 3.0f;

	UPROPERTY()
	FTimerHandle RestartDelay;

	UPROPERTY()
	FScoreBoardData ScoreData;

	virtual void AddKillCount() override;

	virtual void AddDeathCount() override;

	virtual FScoreBoardData GetScoreBoardData() override;

};
