// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCCharacterSelectionGrid.h"

void URCCharacterSelectionGrid::NativeConstruct()
{
	Super::NativeConstruct();

	SlotsPerRow = 3;
}

void URCCharacterSelectionGrid::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCCharacterSelectionGrid::InitGrid(URCCharacterSlotData* slotsData)
{
	CharactersDataObj = slotsData;
	if (CharactersDataObj && SlotWidgetClass)
	{
		TArray<FSlotData> slotsDataArray = CharactersDataObj->CharactersData;
		for (int32 i = 0; i < slotsDataArray.Num(); i++)
		{
			URCCharacterGridSlot* slotWidget = CreateWidget<URCCharacterGridSlot>(this, SlotWidgetClass);//WidgetTree->ConstructWidget<URCCharacterGridSlot>(SlotWidgetClass);
			if (slotWidget)
			{
				slotWidget->OnSlotSelected.AddDynamic(this, &URCCharacterSelectionGrid::SetSelectedSlotWidget);
				slotWidget->InitSlot(slotsDataArray[i]);
				if (SlotGridPanel)
				{
					SlotGridPanel->AddChildToUniformGrid(slotWidget, GetRow(i), GetColumn(i));
				}

				if (i == 0)
				{
					//SelectedSlotWidget = slotWidget;
					slotWidget->SelectSlot();
				}
			}
		}

		
	}
}

FSlotData URCCharacterSelectionGrid::GetSelectedSlotData() const
{
	if (SelectedSlotWidget)
	{
		return SelectedSlotWidget->GetData();
	}
	return FSlotData();
}

FSlotData URCCharacterSelectionGrid::GetRandomSlotData() const
{
	if (CharactersDataObj)
	{
		TArray<FSlotData> slotsDataArray = CharactersDataObj->CharactersData;
		int32 randIndex = FMath::RandRange(0, slotsDataArray.Num() - 1);
		if (slotsDataArray.Num() > 0)
		{
			return slotsDataArray[randIndex];
		}
	}
	return FSlotData();
}

void URCCharacterSelectionGrid::SetSelectedSlotWidget(URCCharacterGridSlot* slotWidget)
{
	if (SelectedSlotWidget)
	{
		SelectedSlotWidget->DeselectSlot();
	}
	SelectedSlotWidget = slotWidget;
}

int32 URCCharacterSelectionGrid::GetRow(int32 index)
{
	return trunc(index / SlotsPerRow);
}

int32 URCCharacterSelectionGrid::GetColumn(int32 index)
{
	return trunc(index % SlotsPerRow);
}
