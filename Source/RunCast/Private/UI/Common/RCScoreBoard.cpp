// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCScoreBoard.h"
#include "UI/Common/ScoreBoardDataContainer.h"

void URCScoreBoard::NativeConstruct()
{
	Super::NativeConstruct();
}

void URCScoreBoard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCScoreBoard::ConstructList(TArray<FScoreBoardData> listData)
{
	ScoreData = listData;
	if (ScoreBoardListView)
	{
		ScoreBoardListView->ClearListItems();
		for (int32 i = 0; i < listData.Num(); i++)
		{
			UScoreBoardDataContainer* dataContainer = NewObject<UScoreBoardDataContainer>(this);
			dataContainer->ScoreData = listData[i];
			ScoreBoardListView->AddItem(dataContainer);
			//ScoreBoardListView->RemoveItem();
		}

	}
}
