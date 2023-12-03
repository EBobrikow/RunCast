// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Common/InGameHUD.h"
#include "UI/Common/RCGameOverlay.h"
#include "UI/DeathMatch/FinaleStat.h"
#include "Characters/RCCharacter.h"
#include "RCDeathMatchHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCDeathMatchHUD : public AInGameHUD
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCGameOverlay> GameOverlayClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UFinaleStat> FinaleStatWidgetClass;

	UFUNCTION()
	void UpdateHealthBar(float val);

	UFUNCTION()
	float GetCharacterHP();

	UFUNCTION()
	void UpdateTimer(int32 min, int32 sec);

	UFUNCTION()
	void DisplayFinaleStat(TArray<FScoreBoardData> data);

protected: 

	UPROPERTY()
	URCGameOverlay* GameOverlayWidget = nullptr;

	UPROPERTY()
	UFinaleStat* FinaleStatWidget = nullptr;

	UPROPERTY()
	ARCCharacter* CharacterRef = nullptr;

	virtual void GameMenuOpened(bool val) override;
	
	
};
