// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RCMainMenuWidget.h"
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
		SoloGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSoloGamePressed);
	}

	if (HostGame_Btn)
	{
		HostGame_Btn->OnClicked.Clear();
		HostGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnHostGamePressed);
		//HostGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnHostGamePressed);
	}

	if (SearchGame_Btn)
	{
		SearchGame_Btn->OnClicked.Clear();
		SearchGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnSearchGamePressed);
	}

	if (ExitGame_Btn)
	{
		ExitGame_Btn->OnClicked.Clear();
		ExitGame_Btn->OnClicked.AddUniqueDynamic(this, &URCMainMenuWidget::OnExitGamePressed);
	}

	if (WB_ServersList)
	{
		WB_ServersList->SetVisibility(ESlateVisibility::Hidden);
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

void URCMainMenuWidget::OnSoloGamePressed()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->StartSoloGame();
	}
}

void URCMainMenuWidget::OnHostGamePressed()
{
	/*if (GameInstancePtr)
	{
		GameInstancePtr->Connect();
	}*/
	if (GameInstancePtr)
	{
		FString msg = "{ CPU: 'Intel', Drives : ['DVD read/writer',	'500 gigabyte hard drive' ]	}";
		//GameInstancePtr->GetServerManager()->GetConnectionManager()->SendRequest(msg);
		GameInstancePtr->GetServerManager()->RequestNewSessionServer("");

		//UGameplayStatics::OpenLevel(this, FName(res));
	}
	
}

void URCMainMenuWidget::OnSearchGamePressed()
{
	if (GameInstancePtr)
	{
		//OnListRecieved
		GameInstancePtr->GetServerManager()->OnServerListRecieved.AddDynamic(this, &URCMainMenuWidget::OnListRecieved);
		GameInstancePtr->GetServerManager()->RequestSessionsList();
	}

	
}

void URCMainMenuWidget::OnExitGamePressed()
{
	if (GameInstancePtr)
	{
		GameInstancePtr->GetServerManager()->GetConnectionManager()->CloseConnection();
	}
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),EQuitPreference::Quit,false);
	//FGenericPlatformMisc::RequestExit(false);
}

void URCMainMenuWidget::OnListRecieved(TArray<FServerInfo> serverList)
{
	FServerInfo tmp = FServerInfo();
	serverList.Add(tmp);
	// construct List
	if (WB_ServersList)
	{
		if (serverList.Num() > 0)
		{
			WB_ServersList->SetVisibility(ESlateVisibility::Visible);
			for (int32 i =0; i < serverList.Num(); i++)
			{
				WB_ServersList->AddListItem(serverList[i]);
			}
		}
		
	}
	
}
