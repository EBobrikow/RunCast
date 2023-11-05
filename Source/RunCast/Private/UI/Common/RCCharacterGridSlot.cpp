// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCCharacterGridSlot.h"

void URCCharacterGridSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (OverlapImg)
	{
		OverlapImg->SetVisibility(ESlateVisibility::Hidden);
	}

	if (SelectedImg)
	{
		SelectedImg->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URCCharacterGridSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCCharacterGridSlot::InitSlot(const FSlotData& slotData)
{
	CharacterData = slotData;

	if (CharacterIcon)
	{
		CharacterIcon->SetBrushFromTexture(CharacterData.CharacteIcon.LoadSynchronous());
	}

	if (CharacterNameTxt)
	{
		CharacterNameTxt->SetText(FText::FromString(slotData.CharacterName));
	}

}

FSlotData URCCharacterGridSlot::GetData() const
{
	return CharacterData;
}

bool URCCharacterGridSlot::IsSelected() const
{
	return SelectedImg->IsVisible();
}

void URCCharacterGridSlot::OnMouseStartOverlap()
{
	if (!IsSelected())
	{
		if (OverlapImg)
		{
			OverlapImg->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void URCCharacterGridSlot::OnMouseEndOverlap()
{
	if (!IsSelected())
	{
		if (OverlapImg)
		{
			OverlapImg->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void URCCharacterGridSlot::OnSlotClicked()
{
	if (IsSelected())
	{
		DeselectSlot();
		if (OverlapImg)
		{
			OverlapImg->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		SelectSlot();
	}
}

void URCCharacterGridSlot::SelectSlot()
{
	if (OverlapImg)
	{
		OverlapImg->SetVisibility(ESlateVisibility::Hidden);
	}

	if (SelectedImg)
	{
		SelectedImg->SetVisibility(ESlateVisibility::Visible);
	}

	if (OnSlotSelected.IsBound())
	{
		OnSlotSelected.Broadcast(this);
	}
}

void URCCharacterGridSlot::DeselectSlot()
{
	if (SelectedImg)
	{
		SelectedImg->SetVisibility(ESlateVisibility::Hidden);
	}
}
