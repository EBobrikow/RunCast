// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Common/RCGameOverlay.h"
#include "Characters/RCCharacter.h"
#include "RCDeathMatchHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCDeathMatchHUD : public AHUD
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCGameOverlay> GameOverlayClass;

	UFUNCTION()
	void UpdateHealthBar(float val);

	UFUNCTION()
	float GetCharacterHP();

protected: 

	UPROPERTY()
	URCGameOverlay* GameOverlayWidget = nullptr;

	UPROPERTY()
	ARCCharacter* CharacterRef = nullptr;


	
	
};
