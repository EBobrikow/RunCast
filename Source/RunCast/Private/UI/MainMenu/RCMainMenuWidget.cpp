// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/RCMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Core/RCGameInstance.h"
#include "Core/RCPlayerController.h"

//#include "ConnectionManager.h"

void URCMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));

	ButtonSetup();
	HideAll();
	LoadPlayerName();
}

void URCMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void URCMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCMainMenuWidget::OnSoloGameClicked()
{
	if (GameInstancePtr)
	{
		//GameInstancePtr->StartSoloGame();
		GameInstancePtr->GetServerManager()->ConnectToMocupServer();
	}

	HideAll();
}

void URCMainMenuWidget::OnHostGameClicked()
{
	//HideAll();

	if (ServerNameBorder)
	{
		//ServerNameBorder->SetVisibility(ESlateVisibility::Visible);
		if (ServerNameBorder->IsVisible())
		{
			HideAll();
		}
		else
		{
			HideAll();
			ServerNameBorder->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
}

void URCMainMenuWidget::OnSearchGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->OnServerListRecieved.Clear();
		GameInstancePtr->GetServerManager()->OnServerListRecieved.AddDynamic(this, &URCMainMenuWidget::OnListRecieved);
		GameInstancePtr->GetServerManager()->RequestSessionsList();
	}
	
	if (ServerListBorder)
	{
		if (ServerListBorder->IsVisible())
		{
			HideAll();
		}
		else
		{
			HideAll();
			ServerListBorder->SetVisibility(ESlateVisibility::Visible);
		}
		

	}

	if (NoAvailableText)
	{
		NoAvailableText->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void URCMainMenuWidget::OnSettingsClicked()
{
	
	if (WB_SettingsMenu)
	{
		if (WB_SettingsMenu->IsVisible())
		{
			HideAll();
			//WB_SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			HideAll();
			WB_SettingsMenu->SetVisibility(ESlateVisibility::Visible);
		}
		
	}
}

void URCMainMenuWidget::OnExitGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->ExitGame();
	}
}

void URCMainMenuWidget::OnRefreshClicked()
{
	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Visible);
	}

	if (WB_ServersList)
	{
		WB_ServersList->ClearList();
	}

	if (NoAvailableText)
	{
		NoAvailableText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->OnServerListRecieved.Clear();
		GameInstancePtr->GetServerManager()->OnServerListRecieved.AddDynamic(this, &URCMainMenuWidget::OnListRecieved);
		GameInstancePtr->GetServerManager()->RequestSessionsList();
	}

	
}

void URCMainMenuWidget::OnCreateServerClicked()
{
	FString servName = "";

	if (ServerNameEdText)
	{
		servName = ServerNameEdText->GetText().ToString();
	}

	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->RequestNewSessionServer(servName);
	}

	CreateServerBtn->SetIsEnabled(false);
	HostGame_Btn->SetIsEnabled(false);
	SoloGame_Btn->SetIsEnabled(false);

	if (LoadingThrobber && LoadingThrobber_1 && FadeBorder)
	{
		LoadingThrobber->SetVisibility(ESlateVisibility::Visible);
		LoadingThrobber_1->SetVisibility(ESlateVisibility::Visible);
		FadeBorder->SetVisibility(ESlateVisibility::Visible);
	}

	GetWorld()->GetTimerManager().ClearTimer(DisableButtonsHandler);
	GetWorld()->GetTimerManager().SetTimer(DisableButtonsHandler, this, &URCMainMenuWidget::EnableButtons, 0.01f, false, 10.0f);
}

void URCMainMenuWidget::OnListRecieved(TArray<FServerInfo> serverList)
{
	GameInstancePtr->GetServerManager()->OnServerListRecieved.RemoveDynamic(this, &URCMainMenuWidget::OnListRecieved);
	// construct List
	if (WB_ServersList)
	{
		WB_ServersList->SetVisibility(ESlateVisibility::Visible);
		if (serverList.Num() > 0)
		{
			for (int32 i =0; i < serverList.Num(); i++)
			{
				WB_ServersList->AddListItem(serverList[i]);
			}
		}
		else
		{
			if (NoAvailableText)
			{
				NoAvailableText->SetVisibility(ESlateVisibility::Visible);
			}
		}
		
	}
	
}

void URCMainMenuWidget::PlayerNameCommited(FString name)
{
	USaveManager* SaveManager = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this))->GetSaveManager();
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
			saveGame->PlayerName = name;
			SaveManager->SaveGameObject(saveGame);

			ARCPlayerController* PC = Cast<ARCPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
			if (GameInstancePtr && PC)
			{
				FPlayerData pData = GameInstancePtr->GetPlayerData();
				pData.PlayerName = name;
				PC->Server_SetPlayerData(pData);
			}
		}
		/*else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}*/

		
	}
}

void URCMainMenuWidget::LoadPlayerName()
{
	USaveManager* SaveManager = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this))->GetSaveManager();
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
			if (saveGame && PlayerNameEdText)
			{
				PlayerNameEdText->SetText(FText::FromString(saveGame->PlayerName));

				ARCPlayerController* PC = Cast<ARCPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				if (GameInstancePtr && PC)
				{
					FPlayerData pData = GameInstancePtr->GetPlayerData();
					pData.PlayerName = saveGame->PlayerName;
					PC->Server_SetPlayerData(pData);
					//GameInstancePtr->SetPlayerData(pData);
					
				}
			}
			
		}
		//else
		//{
		//	saveGame = SaveManager->CreateSaveGameObj();
		//	if (saveGame && PlayerNameEdText)
		//	{
		//		PlayerNameEdText->SetText(FText::FromString("Player1"));

		//		ARCPlayerController* PC = Cast<ARCPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		//		if (GameInstancePtr && PC)
		//		{
		//			FPlayerData pData = GameInstancePtr->GetPlayerData();
		//			pData.PlayerName = "Player1";
		//			PC->Server_SetPlayerData(pData);
		//			//GameInstancePtr->SetPlayerData(pData);
		//		}
		//		SaveManager->SaveGameObject(saveGame);
		//	}
		//}
		
	}
}

void URCMainMenuWidget::HideAll()
{
	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WB_SettingsMenu)
	{
		WB_SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ServerNameBorder)
	{
		ServerNameBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (LoadingThrobber && LoadingThrobber_1 && FadeBorder)
	{
		LoadingThrobber->SetVisibility(ESlateVisibility::Hidden);
		LoadingThrobber_1->SetVisibility(ESlateVisibility::Hidden);
		FadeBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCMainMenuWidget::ButtonSetup()
{
	if (SoloGame_Btn)
	{
		SoloGame_Btn->OnClicked.Clear();
		SoloGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSoloGameClicked);
	}

	if (HostGame_Btn)
	{
		HostGame_Btn->OnClicked.Clear();
		HostGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnHostGameClicked);
	}

	if (Settings_Btn)
	{
		Settings_Btn->OnClicked.Clear();
		Settings_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSettingsClicked);
	}

	if (SearchGame_Btn)
	{
		SearchGame_Btn->OnClicked.Clear();
		SearchGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSearchGameClicked);
	}

	if (ExitGame_Btn)
	{
		ExitGame_Btn->OnClicked.Clear();
		ExitGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnExitGameClicked);
	}

	if (RefreshServerListBtn)
	{
		RefreshServerListBtn->OnClicked.Clear();
		RefreshServerListBtn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnRefreshClicked);
	}

	if (CreateServerBtn)
	{
		CreateServerBtn->OnClicked.Clear();
		CreateServerBtn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnCreateServerClicked);
	}

}

void URCMainMenuWidget::EnableButtons()
{
	CreateServerBtn->SetIsEnabled(true);
	HostGame_Btn->SetIsEnabled(true);
	SoloGame_Btn->SetIsEnabled(true);

	if (LoadingThrobber && LoadingThrobber_1 && FadeBorder)
	{
		LoadingThrobber->SetVisibility(ESlateVisibility::Hidden);
		LoadingThrobber_1->SetVisibility(ESlateVisibility::Hidden);
		FadeBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}
