// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCGameMenuWidget.h"

void URCGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (MainMenu_Btn)
	{
		MainMenu_Btn->OnClicked.Clear();
		MainMenu_Btn->OnClicked.AddUniqueDynamic(this, &URCGameMenuWidget::OnMainMenuClicked);
	}

	if (Settings_Btn)
	{
		Settings_Btn->OnClicked.Clear();
		Settings_Btn->OnClicked.AddUniqueDynamic(this, &URCGameMenuWidget::OnSettingsClicked);
	}

	if (ExitGame_Btn)
	{
		ExitGame_Btn->OnClicked.Clear();
		ExitGame_Btn->OnClicked.AddUniqueDynamic(this, &URCGameMenuWidget::OnExitGameClicked);
	}

	if (SettingsMenu)
	{
		SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCGameMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCGameMenuWidget::OnMainMenuClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->ExitToMainMenu();
	}
}

void URCGameMenuWidget::OnSettingsClicked()
{
	if (SettingsMenu)
	{
		if (SettingsMenu->IsVisible())
		{
			SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			SettingsMenu->SetVisibility(ESlateVisibility::Visible);
		}

	}
}

void URCGameMenuWidget::OnExitGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->ExitGame();
	}
}
