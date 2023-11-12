// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/InGameHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateMenuWidget();
}

void AInGameHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInGameHUD::ShowGameMenu(APlayerController* pc)
{
	if (MenuWidget && pc)
	{
		if (MenuWidget->IsVisible())
		{
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(pc);
			pc->bShowMouseCursor = false;
		}
		else
		{
			MenuWidget->SetVisibility(ESlateVisibility::Visible);
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(pc);
			pc->bShowMouseCursor = true;
		}
	}
	
}

void AInGameHUD::CreateMenuWidget()
{
	if (GameMenuWidgetClass)
	{
		MenuWidget = CreateWidget<URCGameMenuWidget>(GetWorld(), GameMenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}
