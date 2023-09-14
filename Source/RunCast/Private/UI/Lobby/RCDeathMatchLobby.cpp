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
}

void URCDeathMatchLobby::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCDeathMatchLobby::OnReadyButtonClicked()
{
}
