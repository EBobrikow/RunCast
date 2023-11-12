// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathMatch/RCDeathMatchHUD.h"
#include "Core/DeathMatch/RCDeathMatchPC.h"
//#include "Characters/RCCharacter.h"
#include "Components/HealthComponent.h"

void ARCDeathMatchHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameOverlayClass)
	{
		GameOverlayWidget = CreateWidget<URCGameOverlay>(Cast<APlayerController>(GetOwner()), GameOverlayClass);
		if (GameOverlayWidget)
		{
			GameOverlayWidget->AddToViewport();
			if (ARCDeathMatchPC* PC = Cast<ARCDeathMatchPC>(PlayerOwner.Get()))
			{
				CharacterRef = Cast<ARCCharacter>(PC->PossessedCharacter);
				if (CharacterRef)
				{
					UHealthComponent* hpComp = CharacterRef->GetHealthComponent();
					if (hpComp)
					{
						GameOverlayWidget->SetHealthBarValue(hpComp->GetCurrentHealth());
						//hpComp->OnHealthUpdate.AddDynamic(this, &ARCDeathMatchHUD::UpdateHealthBar);
					}
				}
			}
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

float ARCDeathMatchHUD::GetCharacterHP()
{
	if (ARCDeathMatchPC* PC = Cast<ARCDeathMatchPC>(PlayerOwner.Get()))
	{
		CharacterRef = Cast<ARCCharacter>(PC->PossessedCharacter);
		if (CharacterRef)
		{
			UHealthComponent* hpComp = CharacterRef->GetHealthComponent();
			if (hpComp)
			{
				return hpComp->GetCurrentHealth();
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
