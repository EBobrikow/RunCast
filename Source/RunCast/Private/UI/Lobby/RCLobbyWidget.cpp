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
