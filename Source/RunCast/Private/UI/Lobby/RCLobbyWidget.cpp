// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCLobbyWidget.h"
#include "Core/Lobby/RCLobbyPC.h"

void URCLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnBtn)
	{
		ReturnBtn->OnClicked.Clear();
		ReturnBtn->OnClicked.AddUniqueDynamic(this, &URCLobbyWidget::OnReturnClicked);
	}

	if (CreateBtn)
	{
		CreateBtn->OnClicked.Clear();
		CreateBtn->OnClicked.AddUniqueDynamic(this, &URCLobbyWidget::OnCreateClicked);
	}
	
	ARCPlayerController* PC = Cast<ARCPlayerController>(GetOwningPlayer());//UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		FPlayerData pData = PC->GetPlayerData();
		if (pData.PlayerAuthority != ELobbyPlayerAuthority::GameMaster)
		{
			CreateBtn->SetIsEnabled(false);
		}
	}

	FillComboBoxes();

	if (MaxPlayersEdText)
	{
		MaxPlayersEdText->SetText(FText::AsNumber(MaxPlayers));
	}

	SetServerName();
}

void URCLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCLobbyWidget::OnReturnClicked()
{
	URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->ExitToMainMenu();
	}
}

void URCLobbyWidget::OnCreateClicked()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{

		URCGameInstance* GameInstance = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (GameInstance)
		{
			FServerInfo info = GameInstance->GetRemoteServerInfo();
			info.MapName = currentMap.MapName;
			info.MatchType = currentMatch.MatchName;
			info.MaxPlayers = MaxPlayers;
			GameState->Server_UpdateServerInfo(info);
		}
		
	}

	ARCLobbyPC* own = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (own)
	{
		if (currentMatch.MatchType == EMatchType::DeathMatch)
		{
			own->Server_SetNewLobbyState(ELobbyState::DeathMatchLobby);
		}
	}
	

	
}

void URCLobbyWidget::OnMatchSelectionChanged(FString sItem)
{
	for (int32 i = 0; i < matchesData.Num(); i++)
	{
		if (matchesData[i].MatchName == sItem)
		{
			MatchPreviewImg->SetBrushFromTexture(matchesData[i].MatchPreviewImage);
			currentMatch = matchesData[i];
			return;
		}
	}
}

void URCLobbyWidget::OnMapSelectionChanged(FString sItem)
{
	for (int32 i = 0; i < mapsInfo.Num(); i++)
	{
		if (mapsInfo[i].MapName == sItem)
		{
			MapPreviewImg->SetBrushFromTexture(mapsInfo[i].MapPreviewImage);
			currentMap = mapsInfo[i];
			return;
		}
	}
}


void URCLobbyWidget::FillComboBoxes()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		mapsInfo = GameState->GetMapsData();
		for (int32 i = 0; i < mapsInfo.Num(); i++)
		{
			ArenaComboBox->AddOption(mapsInfo[i].MapName);
		}
		if (mapsInfo.Num() > 0)
		{
			ArenaComboBox->SetSelectedOption(mapsInfo[0].MapName);
			MapPreviewImg->SetBrushFromTexture(mapsInfo[0].MapPreviewImage);
			currentMap = mapsInfo[0];
		}
		

		matchesData = GameState->GetMatchesData();
		for (int32 i = 0; i < matchesData.Num(); i++)
		{
			MatchTypeComboBox->AddOption(matchesData[i].MatchName);
		}
		if (matchesData.Num() > 0)
		{
			MatchTypeComboBox->SetSelectedOption(matchesData[0].MatchName);
			MaxPlayers = matchesData[0].DefaultMaxPlayers;
			MatchPreviewImg->SetBrushFromTexture(matchesData[0].MatchPreviewImage);
			currentMatch = matchesData[0];

		}
		//MatchTypeComboBox->GetSelectedOption();
	}
}

void URCLobbyWidget::SetServerName()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		FServerInfo info = GameState->GetSuncServerInfo();
		if (info.Id != -1)
		{
			GetWorld()->GetTimerManager().ClearTimer(ServerNameAwaitTimer);
			ServerName->SetText(FText::FromString(info.ServerName));
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(ServerNameAwaitTimer);
			GetWorld()->GetTimerManager().SetTimer(ServerNameAwaitTimer, this, &URCLobbyWidget::SetServerName, 0.01f, false, AwaitRate);
		}
	}
}


