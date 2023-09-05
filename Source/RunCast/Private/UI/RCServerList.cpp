// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RCServerList.h"
#include "UI/RCListViewDataContainer.h"

void URCServerList::NativeConstruct()
{
	Super::NativeConstruct();
}

void URCServerList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCServerList::AddListItem(FServerInfo& data)
{
	URCListViewDataContainer* dataContainer = NewObject<URCListViewDataContainer>(this);
	dataContainer->serverInfoData = data;
	if (ListView)
	{
		ListView->AddItem(dataContainer);
	}
}

void URCServerList::ClearList()
{
	if (ListView)
	{
		ListView->ClearListItems();
	}
}
