// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Abilities/BaseAbilityWidget.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"

void UBaseAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ARCDeathMatchHUD* hud = GetOwningPlayer()->GetHUD<ARCDeathMatchHUD>())
	{
		hud->OnTagCooldownUpdate.AddDynamic(this, &UBaseAbilityWidget::OnTagCooldownRecieved);
		hud->OnClearCooldownUI.AddDynamic(this, &UBaseAbilityWidget::ClearCooldownTriggered);
	}
}

void UBaseAbilityWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBaseAbilityWidget::OnTagCooldownRecieved(FGameplayTag Tag, float renmaining, float duration)
{
	if (Tag.MatchesTagExact(RelatedCooldownTag))// == RelatedCooldownTag)
	{
		RelatedCooldownTagRecieved(renmaining, duration);		
	}
}

void UBaseAbilityWidget::RelatedCooldownTagRecieved(float renmaining, float duration)
{

}

void UBaseAbilityWidget::ClearCooldownTriggered()
{
	ClearCooldownUI();
}

void UBaseAbilityWidget::ClearCooldownUI()
{
}
