// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCDeathMatchLobby.h"
//#include "Core/RCPlayerController.h"
#include "Core/Lobby/RCLobbyPC.h"
#include "UI/Lobby/RCPlayerListViewContainer.h"

void URCDeathMatchLobby::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReadyBtn)
	{
		ReadyBtn->OnClicked.Clear();
		ReadyBtn->OnClicked.AddUniqueDynamic(this, &URCDeathMatchLobby::OnReadyButtonClicked);
	}
	
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		localPlayerList = GameState->GetPlayerDataList();
		GameState->OnPlayersListChanged.AddDynamic(this, &URCDeathMatchLobby::CreatePlayerList);
		CreatePlayerList(localPlayerList);

		GameState->OnSyncInfoChanged.AddDynamic(this, &URCDeathMatchLobby::FillServerInfo);
		FServerInfo  servInfo = GameState->GetSyncServerInfo();
		FillServerInfo(servInfo);
		
	}

	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		PC->UpdatePlayerToServer();
	}
	

}

void URCDeathMatchLobby::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCDeathMatchLobby::OnReadyButtonClicked()
{
	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		PC->PlayerReadyClicked();
	}
}

void URCDeathMatchLobby::CreatePlayerList(TArray<FPlayerData> list)
{
	localPlayerList = list;
	if (PlayersListView)
	{
		PlayersListView->ClearListItems();
		for (int32 i = 0; i < localPlayerList.Num(); i++)
		{
			URCPlayerListViewContainer* dataContainer = NewObject<URCPlayerListViewContainer>(this);
			dataContainer->PlayerData = localPlayerList[i];
			PlayersListView->AddItem(dataContainer);
		}
		
	}
}

void URCDeathMatchLobby::FillServerInfo(FServerInfo info)
{
	FString servName = ServerNameText->GetText().ToString();
	if (info.Id != -1 && servName != info.ServerName)
	{
		if (ServerNameText)
		{
			ServerNameText->SetText(FText::FromString(info.ServerName));
		}
		if (MatchTypeText)
		{
			MatchTypeText->SetText(FText::FromString(info.MatchType));
		}
		if (MapNameText)
		{
			MapNameText->SetText(FText::FromString(info.MapName));
		}
	}
}
