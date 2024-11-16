// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathMatch/RCDeathMatchHUD.h"
#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "AbilitySystemInterface.h"

void ARCDeathMatchHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameOverlayClass)
	{
		GameOverlayWidget = CreateWidget<URCGameOverlay>(Cast<APlayerController>(GetOwner()), GameOverlayClass);
		if (GameOverlayWidget)
		{
			GameOverlayWidget->AddToViewport();
			
		}
	}
}

void ARCDeathMatchHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARCDeathMatchHUD::UpdateHealthBar(float val)
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->SetHealthBarValue(val);
	}
	
}

void ARCDeathMatchHUD::UpdateTagRelatedCooldown(const FGameplayTag& Tag, const float& renmaining, const float& duration)
{
	if (OnTagCooldownUpdate.IsBound())
	{
		OnTagCooldownUpdate.Broadcast(Tag, renmaining, duration);
	}
}

void ARCDeathMatchHUD::ClearCooldowns()
{
	if (OnClearCooldownUI.IsBound())
	{
		OnClearCooldownUI.Broadcast();
	}
}

float ARCDeathMatchHUD::GetCharacterHP()
{
	if (ARCDeathMatchPC* PC = Cast<ARCDeathMatchPC>(PlayerOwner.Get()))
	{
		CharacterRef = Cast<ARCCharacter>(PC->PossessedCharacter);
		if (CharacterRef)
		{
			auto Attrib = CharacterRef->GetAttributes();
			if (Attrib)
			{
				return Attrib->GetHealth();
			}			
		}
	}
	
	return 0.0f;
}

void ARCDeathMatchHUD::UpdateTimer(int32 min, int32 sec)
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->SetTime(min, sec);
	}
}

void ARCDeathMatchHUD::DisplayFinaleStat(TArray<FScoreBoardData> data)
{
	if (FinaleStatWidgetClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		FinaleStatWidget = CreateWidget<UFinaleStat>(PC, FinaleStatWidgetClass);
		if (FinaleStatWidget)
		{
			FinaleStatWidget->AddToViewport();
			FinaleStatWidget->Init(data);
		}
	}
}

void ARCDeathMatchHUD::DisplayDamageDirection(AActor* source)
{
	if (DamageDirectionWidgetClass)
	{
		URCDamageDirectionWidget* DamageDirectionWidget = CreateWidget<URCDamageDirectionWidget>(Cast<APlayerController>(GetOwner()), DamageDirectionWidgetClass);
		if (DamageDirectionWidget)
		{
			DamageDirectionWidget->DamageSource = source;
			DamageDirectionWidget->InitAnimation();
			DamageDirectionWidget->AddToViewport();
		}
	}
}

void ARCDeathMatchHUD::KillAnnounce(FString killerName, EWeaponIconType weaponIconType, FString victimName)
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->SetKillAnnounce(killerName, weaponIconType, victimName);
	}
}

void ARCDeathMatchHUD::GameMenuOpened(bool val)
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->ShowCrosshair(val);
	}
}
