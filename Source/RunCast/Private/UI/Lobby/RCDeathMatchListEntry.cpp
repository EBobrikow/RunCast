// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/RCDeathMatchListEntry.h"

void URCDeathMatchListEntry::NativeConstruct()
{
	Super::NativeConstruct();
}

void URCDeathMatchListEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);
}

void URCDeathMatchListEntry::SetTextureToImage(UImage* Img, UTexture2D* texture)
{
	if (Img)
	{
		Img->SetBrushFromTexture(texture);
	}
}
