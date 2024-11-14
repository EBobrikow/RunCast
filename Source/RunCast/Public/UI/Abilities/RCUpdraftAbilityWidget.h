// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Abilities/BaseAbilityWidget.h"
#include "Components/ProgressBar.h"
#include "RCUpdraftAbilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCUpdraftAbilityWidget : public UBaseAbilityWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* CooldownProgressBar;

	virtual void RelatedCooldownTagRecieved(float renmaining, float duration) override;
	
};
