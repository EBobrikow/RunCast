// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/Announcer/KillAnnouncerListEntry.h"
#include "UI/Common/Announcer/KillAnnouncerDataContainer.h"
#include "UI/Common/Announcer/KillAnnouncerBoard.h"

void UKillAnnouncerListEntry::NativeConstruct()
{
	Super::NativeConstruct();
}

void UKillAnnouncerListEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UKillAnnouncerListEntry::SetListEntryData(UObject* dataObject)
{
	CashedDataContainer = dataObject;
	if (UKillAnnouncerDataContainer* dataContainer = Cast<UKillAnnouncerDataContainer>(dataObject))
	{
		if (KillerNameTxt)
		{
			KillerNameTxt->SetText(FText::FromString(dataContainer->KillerName));
		}

		if (WeaponIcon)
		{
			if (IconsMap.Contains(dataContainer->WeaponIconType))
			{
				WeaponIcon->SetBrushFromTexture(IconsMap[dataContainer->WeaponIconType]);
			}
		
		}

		if (VictimNameTxt)
		{
			VictimNameTxt->SetText(FText::FromString(dataContainer->VicitimName));
		}

		
		GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &UKillAnnouncerListEntry::LifeTimeEnd, ItemLifeTime, false);

		
	}
}

void UKillAnnouncerListEntry::LifeTimeEnd()
{
	if (CashedDataContainer)
	{
		if (UKillAnnouncerBoard* outer = Cast<UKillAnnouncerBoard>(CashedDataContainer->GetOuter()))
		{
			outer->RemoveItem(CashedDataContainer);
		}
	}
	
}
