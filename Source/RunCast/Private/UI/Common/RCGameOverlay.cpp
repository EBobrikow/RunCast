// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCGameOverlay.h"

void URCGameOverlay::NativeConstruct()
{
	Super::NativeConstruct();
}

void URCGameOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCGameOverlay::SetHealthBarValue(float val)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(val/100.0f);
	}
}

void URCGameOverlay::SetTime(int32 Min, int32 Sec)
{
	if (MinutesTxt && SecondsTxt)
	{
		MinutesTxt->SetText(FText::FromString(FString::FromInt(Min)));
		SecondsTxt->SetText(FText::FromString(FString::FromInt(Sec)));
	}
}

void URCGameOverlay::ShowCrosshair(bool val)
{
	if (val)
	{
		CrosshairImg->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CrosshairImg->SetVisibility(ESlateVisibility::Hidden);
	}
}

URCDashAbilityWidget* URCGameOverlay::GetDashAbilityWidget() const
{
	return DashAbilityWidget;
}
