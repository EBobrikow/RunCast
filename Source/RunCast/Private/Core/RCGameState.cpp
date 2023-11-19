// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RCGameState.h"
#include "Core/RCGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/ScoreBoardInterface.h"

void ARCGameState::BeginPlay()
{
	Super::BeginPlay();

}

void ARCGameState::Server_UpdateScoreBoard_Implementation()
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), Controllers);

	for (AActor* cntrl : Controllers)
	{
		ScoreBoardTable.Empty();
		IScoreBoardInterface* scoreContrl = Cast<IScoreBoardInterface>(cntrl);
		if (scoreContrl)
		{
			ScoreBoardTable.Add(scoreContrl->GetScoreBoardData());
		}
	}
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


