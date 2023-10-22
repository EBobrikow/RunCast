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
