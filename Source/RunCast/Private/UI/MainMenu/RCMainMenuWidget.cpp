// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/RCMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Core/RCGameInstance.h"
//#include "ConnectionManager.h"

void URCMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstancePtr = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (SoloGame_Btn)
	{
		SoloGame_Btn->OnClicked.Clear();
		SoloGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSoloGameClicked);
	}

	if (HostGame_Btn)
	{
		HostGame_Btn->OnClicked.Clear();
		HostGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnHostGameClicked);
		//HostGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnHostGamePressed);
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

	if (Settings_Btn)
	{
		Settings_Btn->OnClicked.Clear();
		Settings_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSettingsClicked);
	}

	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WB_SettingsMenu)
	{
		WB_SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
	}
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
		GameInstancePtr->StartSoloGame();
	}

	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCMainMenuWidget::OnHostGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->RequestNewSessionServer("");
	}

	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void URCMainMenuWidget::OnSearchGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->OnServerListRecieved.AddDynamic(this, &URCMainMenuWidget::OnListRecieved);
		GameInstancePtr->GetServerManager()->RequestSessionsList();
	}

	if (ServerListBorder)
	{
		ServerListBorder->SetVisibility(ESlateVisibility::Visible);

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
			WB_SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			WB_SettingsMenu->SetVisibility(ESlateVisibility::Visible);
		}
		
	}
}

void URCMainMenuWidget::OnExitGameClicked()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->GetConnectionManager()->CloseConnection();
	}
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),EQuitPreference::Quit,false);
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
		GameInstancePtr->GetServerManager()->OnServerListRecieved.AddDynamic(this, &URCMainMenuWidget::OnListRecieved);
		GameInstancePtr->GetServerManager()->RequestSessionsList();
	}

	
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
