// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCLobbyWidget.h"

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
	

	FillComboBoxes();

	if (MaxPlayersEdText)
	{
		MaxPlayersEdText->SetText(FText::AsNumber(MaxPlayers));
	}

}

void URCLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCLobbyWidget::OnReturnClicked()
{
}

void URCLobbyWidget::OnCreateClicked()
{
}


void URCLobbyWidget::FillComboBoxes()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		TArray<FArenaMapData> mapsInfo = GameState->GetMapsData();
		for (int32 i = 0; i < mapsInfo.Num(); i++)
		{
			ArenaComboBox->AddOption(mapsInfo[i].MapName);
		}
		if (mapsInfo.Num() > 0)
		{
			ArenaComboBox->SetSelectedOption(mapsInfo[0].MapName);
		}
		

		TArray<FArenaMatchData> matchesData = GameState->GetMatchesData();
		for (int32 i = 0; i < matchesData.Num(); i++)
		{
			MatchTypeComboBox->AddOption(matchesData[i].MatchName);
		}
		if (matchesData.Num() > 0)
		{
			MatchTypeComboBox->SetSelectedOption(matchesData[0].MatchName);
			MaxPlayers = matchesData[0].DefaultMaxPlayers;
		}
		//MatchTypeComboBox->GetSelectedOption();
	}
}


