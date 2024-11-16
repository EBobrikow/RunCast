// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameState.h"
#include "Core/RCGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/ScoreBoardInterface.h"
#include "Actors/Weapons/DynamiteBox.h"
#include "Characters/RCCharacter.h"

void ARCGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		ARCGameMode* GM = Cast<ARCGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->OnMatchEnd.AddDynamic(this, &ARCGameState::OnMatchEnd);
		}
	}
}

void ARCGameState::Server_AnounceCharacterKilled_Implementation(AActor* killer, ACharacter* victim)
{
	EWeaponIconType iconType = EWeaponIconType::None;
	FString killerName = "";
	FString victimName = "";

	if (killer)
	{
		if (ARCCharacter* killerCharacter = Cast<ARCCharacter>(killer))
		{
			if (killerCharacter->HoldWeaponRef)
			{
				iconType = killerCharacter->HoldWeaponRef->GetWeaponTypeIcon();
				if (IScoreBoardInterface* scoreBoardInterface = Cast<IScoreBoardInterface>(killerCharacter->GetController()))
				{
					killerName = scoreBoardInterface->GetScoreBoardData().PlayerName;
				}
			}
		}
		else if (ADynamiteBox* box = Cast<ADynamiteBox>(killer))
		{
			iconType = EWeaponIconType::Dynamite;
		}
	}

	if (victim)
	{
		if (IScoreBoardInterface* scoreBoardInterface = Cast<IScoreBoardInterface>(victim->GetController()))
		{
			victimName = scoreBoardInterface->GetScoreBoardData().PlayerName;
		}
	}

	Multicast_AnounceCharacterKilled(killerName, iconType, victimName);
}

void ARCGameState::Multicast_AnounceCharacterKilled_Implementation(const FString& killerName, EWeaponIconType weaponIconType, const FString& victimName)
{
	if (OnCharacterKillAnounce.IsBound())
	{
		OnCharacterKillAnounce.Broadcast(killerName, weaponIconType, victimName);
	}
}

void ARCGameState::Multicast_FinaleScoreData_Implementation(const TArray<FScoreBoardData>& scoreList)
{
	if (OnShowFinaleStat.IsBound())
	{
		OnShowFinaleStat.Broadcast(scoreList);
	}
}

void ARCGameState::SortScoreBoard()
{
	FScoreBoardData tmp;
	for (int32 i = 0; i < ScoreBoardTable.Num(); i++)
	{
		for (int32 j = 0; j < ScoreBoardTable.Num(); j++)
		{
			if (j + 1 <= ScoreBoardTable.Num() - 1)
			{
				if (ScoreBoardTable[j].KillCount < ScoreBoardTable[j+1].KillCount)
				{
					tmp = ScoreBoardTable[j];
					ScoreBoardTable[j] = ScoreBoardTable[j+1];
					ScoreBoardTable[j + 1] = tmp;
				}
			}
		}
	}
}

void ARCGameState::UpdateScoreBoard()
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), Controllers);

	ScoreBoardTable.Empty();
	for (AActor* cntrl : Controllers)
	{

		IScoreBoardInterface* scoreContrl = Cast<IScoreBoardInterface>(cntrl);
		if (scoreContrl)
		{
			ScoreBoardTable.Add(scoreContrl->GetScoreBoardData());
		}
	}
}

void ARCGameState::OnMatchEnd()
{
	UpdateScoreBoard();
	SortScoreBoard();
	Multicast_FinaleScoreData(ScoreBoardTable);
}

void ARCGameState::Server_UpdateScoreBoard_Implementation()
{
	UpdateScoreBoard();
	SortScoreBoard();
	Multicast_OnScoreUpdated(ScoreBoardTable);
}

void ARCGameState::Multicast_OnScoreUpdated_Implementation(const TArray<FScoreBoardData>& scoreList)
{
	ScoreBoardTable = scoreList;
	if (OnScoreBoardUpdate.IsBound())
	{
		OnScoreBoardUpdate.Broadcast(scoreList);
	}
}


