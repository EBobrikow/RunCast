// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI/Abilities/RCDashAbilityWidget.h"
#include "RCGameOverlay.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCGameOverlay : public UUserWidget
{
	GENERATED_BODY()

public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SetHealthBarValue(float val);

	UFUNCTION()
	void SetTime(int32 Min, int32 Sec);

	void ShowCrosshair(bool val);

	URCDashAbilityWidget* GetDashAbilityWidget() const;

protected: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CrosshairImg;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MinutesTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SecondsTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCDashAbilityWidget* DashAbilityWidget;

};
