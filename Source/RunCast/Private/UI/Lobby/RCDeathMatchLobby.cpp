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
	
	/*ARCPlayerController* PC = Cast<ARCPlayerController>(GetOwningPlayer());
	if (PC)
	{
		PC->UpdatePlayerToServer();
	}*/
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		localPlayerList = GameState->GetPlayerDataList();
		GameState->OnPlayersListChanged.AddDynamic(this, &URCDeathMatchLobby::CreatePlayerList);
		CreatePlayerList(localPlayerList);

		FServerInfo  servInfo = GameState->GetSyncServerInfo();
		if (servInfo.Id != -1)
		{
			if (ServerNameText)
			{
				ServerNameText->SetText(FText::FromString(servInfo.ServerName));
			}
			if (MatchTypeText)
			{
				MatchTypeText->SetText(FText::FromString(servInfo.MatchType));
			}
			if (MapNameText)
			{
				MapNameText->SetText(FText::FromString(servInfo.MapName));
			}
		}
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
