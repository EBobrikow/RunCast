// Copyright:       Copyright (C) 2022 Doğa Can Yanıkoğlu
// Source Code:     https://github.com/dyanikoglu/ALS-Community

#include "AI/ALS_BTTask_SetFocusToPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UALS_BTTask_SetFocusToPlayer::UALS_BTTask_SetFocusToPlayer()
{
	NodeName = "ALS Focus On Player";
}

EBTNodeResult::Type UALS_BTTask_SetFocusToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), Characters);

	FVector selfLoc = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	AActor* target = nullptr;

	for (AActor* character : Characters)
	{
		if (character == OwnerComp.GetAIOwner()->GetPawn())
		{
			continue;
		}

		double distLoc = FVector::Dist(selfLoc, character->GetActorLocation());
		if (distLoc < 3000)
		{
			if (target)
			{
				if (distLoc < FVector::Dist(selfLoc, target->GetActorLocation()))
				{
					target = character;
				}
			}
			else
			{
				target = character;
			}
			
		}
	
	}

	//APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (target)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, target);
		OwnerComp.GetAIOwner()->SetFocus(target);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString UALS_BTTask_SetFocusToPlayer::GetStaticDescription() const
{
	return "ALS Set Focus to player's pawn";
}
