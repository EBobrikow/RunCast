// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Abilities/RCDashAbilityWidget.h"

void URCDashAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CooldownProgressBar)
	{
		CooldownProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCDashAbilityWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void URCDashAbilityWidget::SetCooldownProgress(float remainingTime, float Duration)
{
	if (CooldownProgressBar)
	{
		CooldownProgressBar->SetVisibility(ESlateVisibility::Visible);
		CooldownProgressBar->SetPercent(1.0f - remainingTime / Duration);
	}
}

void URCDashAbilityWidget::FinishCooldown()
{
	if (CooldownProgressBar)
	{
		CooldownProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}
