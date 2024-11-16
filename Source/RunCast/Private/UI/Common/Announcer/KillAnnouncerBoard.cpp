// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/Announcer/KillAnnouncerBoard.h"


void UKillAnnouncerBoard::NativeConstruct()
{
	Super::NativeConstruct();

	if (AnnouncerListView)
	{
		AnnouncerListView->ClearListItems();
	}
}

void UKillAnnouncerBoard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UKillAnnouncerBoard::AddKillAnnounce(FString killerName, EWeaponIconType weaponIconType, FString victimName)
{
	if (AnnouncerListView)
	{
		UKillAnnouncerDataContainer* dataContainer = NewObject<UKillAnnouncerDataContainer>(this);
		dataContainer->KillerName = killerName;
		dataContainer->WeaponIconType = weaponIconType;
		dataContainer->VicitimName = victimName;

		AnnouncerListView->AddItem(dataContainer);
	}
}

void UKillAnnouncerBoard::RemoveItem(UObject* itemObj)
{
	if (AnnouncerListView)
	{
		AnnouncerListView->RemoveItem(itemObj);
		AnnouncerListView->RequestRefresh();
	}
}
