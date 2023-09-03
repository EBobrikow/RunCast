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
		SoloGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnSoloGamePressed);
	}

	if (HostGame_Btn)
	{
		HostGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnHostGamePressed);
	}

	if (SearchGame_Btn)
	{
		SearchGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnSearchGamePressed);
	}

	if (ExitGame_Btn)
	{
		ExitGame_Btn->OnPressed.AddDynamic(this, &URCMainMenuWidget::OnExitGamePressed);
	}

	
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
	}
	
}

void URCMainMenuWidget::OnSearchGamePressed()
{
	
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
