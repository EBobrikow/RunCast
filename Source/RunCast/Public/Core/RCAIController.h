// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/ALSAIController.h"
#include "Tools/Globals.h"
#include "RCAIController.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCAIController : public AALSAIController
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
	void CharacterKilled();


	UFUNCTION()
	void Restart();

	UPROPERTY()
	FPlayerData PlayerData;

	UPROPERTY()
	float RestartDelayTime = 3.0f;

	UPROPERTY()
	FTimerHandle RestartDelay;

};
