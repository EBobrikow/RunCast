// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Common/InGameHUD.h"
#include "UI/Common/RCGameOverlay.h"
#include "UI/DeathMatch/FinaleStat.h"
#include "Characters/RCCharacter.h"
#include "UI/Common/RCDamageDirectionWidget.h"
#include "RCDeathMatchHUD.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTagCooldownUpdate, FGameplayTag, Tag, float, remaining, float, duration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearCooldownUI);

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCDamageDirectionWidget> DamageDirectionWidgetClass;

	UFUNCTION()
	void UpdateHealthBar(float val);

	UFUNCTION()
	void UpdateTagRelatedCooldown(const FGameplayTag& Tag, const float& renmaining, const float& duration);

	UFUNCTION()
	void ClearCooldowns();

	UFUNCTION()
	float GetCharacterHP();

	UFUNCTION()
	void UpdateTimer(int32 min, int32 sec);

	UFUNCTION()
	void DisplayFinaleStat(TArray<FScoreBoardData> data);

	UFUNCTION()
	void DisplayDamageDirection(AActor* source);

	UPROPERTY()
	FOnTagCooldownUpdate OnTagCooldownUpdate;

	UPROPERTY()
	FOnClearCooldownUI OnClearCooldownUI;

	UFUNCTION()
	void KillAnnounce(FString killerName, EWeaponIconType weaponIconType, FString victimName);

protected: 

	UPROPERTY()
	URCGameOverlay* GameOverlayWidget = nullptr;

	UPROPERTY()
	UFinaleStat* FinaleStatWidget = nullptr;

	UPROPERTY()
	ARCCharacter* CharacterRef = nullptr;

	virtual void GameMenuOpened(bool val) override;
	
	
};
