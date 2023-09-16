// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCDeathMatchLobby.h"

void URCDeathMatchLobby::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReadyBtn)
	{
		ReadyBtn->OnClicked.Clear();
		ReadyBtn->OnClicked.AddUniqueDynamic(this, &URCDeathMatchLobby::OnReadyButtonClicked);
	}

	/*ARCPlayerController* PC = Cast<ARCPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		FPlayerData pData = PC->GetPlayerData();
		if (pData.PlayerAuthority != ELobbyPlayerAuthority::GameMaster)
		{
			CreateBtn->SetIsEnabled(false);
		}
	}*/
}

void URCDeathMatchLobby::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCDeathMatchLobby::OnReadyButtonClicked()
{
}
