// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCLobbyHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ARCLobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		GameState->OnLobbyStateChanged.AddDynamic(this, &ARCLobbyHUD::CreateWidgetByLobbyState);
		CreateWidgetByLobbyState(GameState->GetCurrentLobbyState());
	}

	//APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//if (PC)
	//{
	//	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
	//	PC->bShowMouseCursor = true;
	//}
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

		CreateWidgetByClass(LobbyEntranceWidgetClass);
		
		break;
	case ELobbyState::DeathMatchLobby:

		CreateWidgetByClass(DeathMatchLobbyWidgetClass);

		break;
	default:
		break;
	}
}

void ARCLobbyHUD::CreateWidgetByClass(TSubclassOf<UUserWidget> widgetClass)
{
	if (widgetClass)
	{
		if (CurrentWidget)
		{
			CurrentWidget->RemoveFromViewport();
		}
		PreviosWidget = CurrentWidget;
		auto PC = GetOwner();
		CurrentWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(GetOwner()), widgetClass);
		CurrentWidget->AddToViewport();
	}
}
