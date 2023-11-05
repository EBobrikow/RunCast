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

	if (AddBotBtn)
	{
		AddBotBtn->OnClicked.Clear();
		AddBotBtn->OnClicked.AddUniqueDynamic(this, &URCDeathMatchLobby::OnAddBotButtonClicked);
		AddBotBtn->SetVisibility(ESlateVisibility::Hidden);
	}

	if (RemoveBotBtn)
	{
		RemoveBotBtn->OnClicked.Clear();
		RemoveBotBtn->OnClicked.AddUniqueDynamic(this, &URCDeathMatchLobby::OnRemoveBotButtonClicked);
		RemoveBotBtn->SetVisibility(ESlateVisibility::Hidden);
	}
	
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		localPlayerList = GameState->GetPlayerDataList();
		GameState->OnPlayersListChanged.AddDynamic(this, &URCDeathMatchLobby::CreatePlayerList);
		CreatePlayerList(localPlayerList);
	}

	FillInfo();

	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		PC->UpdatePlayerToServer();

		FPlayerData pData = PC->GetPlayerData();
		if (pData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
		{
			AddBotBtn->SetVisibility(ESlateVisibility::Visible);
			RemoveBotBtn->SetVisibility(ESlateVisibility::Visible);
			//CreateBtn->SetIsEnabled(false);
		}
	}
	
	CreateSelectionGrid();
}

void URCDeathMatchLobby::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCDeathMatchLobby::OnAddBotButtonClicked()
{
	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		FPlayerData pData = PC->GetPlayerData();
		if (pData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
		{
			if (CharacterSelection)
			{
				FSlotData slotData = CharacterSelection->GetRandomSlotData();
				PC->AddBotClicked(slotData.CharacterClass);
			}
		}
	}
}

void URCDeathMatchLobby::OnRemoveBotButtonClicked()
{
	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		FPlayerData pData = PC->GetPlayerData();
		if (pData.PlayerAuthority == ELobbyPlayerAuthority::GameMaster)
		{
			PC->RemoveBotClicked();
		}
	}
}

void URCDeathMatchLobby::OnReadyButtonClicked()
{


	ARCLobbyPC* PC = Cast<ARCLobbyPC>(GetOwningPlayer());
	if (PC)
	{
		FPlayerData PD = PC->GetPlayerData();
		if (CharacterSelection)
		{
			FSlotData slotData = CharacterSelection->GetSelectedSlotData();
			PD.SelectedCharacterClass = slotData.CharacterClass;
			PC->SetPlayerData(PD);
		}
		
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
	if (info.Id != -1)
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

void URCDeathMatchLobby::CreateSelectionGrid()
{
	if (CharactersSlotsDataClass)
	{
		URCCharacterSlotData* slotsDataObj = NewObject<URCCharacterSlotData>(this, CharactersSlotsDataClass);
		if (CharacterSelection && slotsDataObj)
		{
			CharacterSelection->InitGrid(slotsDataObj);
		}
	}
}

void URCDeathMatchLobby::FillInfo()
{
	ARCLobbyGameState* GameState = GetWorld()->GetGameState<ARCLobbyGameState>();
	if (GameState)
	{
		FServerInfo  servInfo = GameState->GetSyncServerInfo();
		if (servInfo.MapName.IsEmpty() && servInfo.MatchType.IsEmpty())
		{
			GetWorld()->GetTimerManager().ClearTimer(FillInfoTimer);
			GetWorld()->GetTimerManager().SetTimer(FillInfoTimer, this, &URCDeathMatchLobby::FillInfo, 1.0f, false);
		}
		else
		{
			FillServerInfo(servInfo);
		}

		
	}
	
}
