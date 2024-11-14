// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Abilities/RCDashAbilityWidget.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"

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
		
		float percent = 1.0f - remainingTime / Duration;
		//UE_LOG(LogTemp, Warning, TEXT("Percent: %f"), percent);
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

void URCDashAbilityWidget::RelatedCooldownTagRecieved(float renmaining, float duration)
{
	SetCooldownProgress(renmaining, duration);
}

