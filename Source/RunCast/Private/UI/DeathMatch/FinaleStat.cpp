// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathMatch/FinaleStat.h"
#include "Core/RCGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UFinaleStat::NativeConstruct()
{
	Super::NativeConstruct();

	if (ContinueBtn)
	{
		ContinueBtn->OnClicked.AddDynamic(this, &UFinaleStat::OnContinueClicked);
	}
}

void UFinaleStat::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UFinaleStat::Init(TArray<FScoreBoardData> data)
{
	if (BP_ScoreBoard)
	{
		BP_ScoreBoard->ConstructList(data);
	}

	if (WinnerTxt)
	{
		if (data.Num() > 0)
		{
			FString txt;
			if (data[0].KillCount == 0)
			{
				txt = "Draw";
			}
			else
			{
				txt = "Winner " + data[0].PlayerName;
			}
			
			WinnerTxt->SetText(FText::FromString(txt));
		}
		
	}
}

void UFinaleStat::OnContinueClicked()
{
	URCGameInstance* gameInst = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInst)
	{
		gameInst->ExitToMainMenu();
	}
}
