// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCLobbyHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ARCLobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	GameState->OnLobbyStateChanged.AddDynamic(this, &ARCLobbyHUD::CreateWidgetByLobbyState);
	if (GameState)
	{
		CreateWidgetByLobbyState(GameState->GetCurrentLobbyState());
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
		PC->bShowMouseCursor = true;
	}
}

void ARCLobbyHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARCLobbyHUD::CreateWidgetByLobbyState(ELobbyState state)
{
	switch (state)
	{
	case ELobbyState::Entrance:
		if (LobbyEntranceWidgetClass)
		{
			if (CurrentWidget)
			{
				CurrentWidget->RemoveFromViewport();
			}

			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), LobbyEntranceWidgetClass);
			CurrentWidget->AddToViewport();
		}
		
		break;
	case ELobbyState::DeathMatchLobby:
		break;
	default:
		break;
	}
}
