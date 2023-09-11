// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/RCMainMenuHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ARCMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		if (MainMenuWidget)
		{
			MainMenuWidget->RemoveFromViewport();
		}

		MainMenuWidget = CreateWidget<URCMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
	}

	/*APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
		PC->bShowMouseCursor = true;
	}*/
}
