// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/RCServerListViewItem.h"

void URCServerListViewItem::NativeConstruct()
{
	Super::NativeConstruct();

	GameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (JoinServerBtn)
	{
		JoinServerBtn->OnClicked.AddDynamic(this, &URCServerListViewItem::OnJoinButtonClicked);
	}
}

void URCServerListViewItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCServerListViewItem::OnJoinButtonClicked()
{
	if (GameInst)
	{
		GameInst->GetServerManager()->ConnectToUEServer(serverInfoData);
	}
}
