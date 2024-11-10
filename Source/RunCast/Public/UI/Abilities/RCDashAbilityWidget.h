// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "RCDashAbilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCDashAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetCooldownProgress(float remainingTime, float Duration);
	void FinishCooldown();

protected: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* CooldownProgressBar;
	
};
