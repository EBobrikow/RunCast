// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Abilities/RCUpdraftAbilityWidget.h"

void URCUpdraftAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CooldownProgressBar)
	{
		CooldownProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCUpdraftAbilityWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCUpdraftAbilityWidget::RelatedCooldownTagRecieved(float renmaining, float duration)
{
	if (CooldownProgressBar)
	{
		float percent = 1.0f - renmaining / duration;
		CooldownProgressBar->SetPercent(percent);
		if (percent > 0.99f)
		{
			CooldownProgressBar->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			CooldownProgressBar->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void URCUpdraftAbilityWidget::ClearCooldownUI()
{
	if (CooldownProgressBar)
	{
		CooldownProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}
