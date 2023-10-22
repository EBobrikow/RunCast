// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
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

protected: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CrosshairImg;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

};
