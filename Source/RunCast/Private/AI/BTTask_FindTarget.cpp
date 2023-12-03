// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindTarget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Characters/RCCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindTarget::UBTTask_FindTarget()
{
	NodeName = "Find Target";
}

EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARCCharacter::StaticClass(), Characters);

	FVector selfLoc = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	AActor* target = nullptr;

	for (AActor* character : Characters)
	{
		if (character == OwnerComp.GetAIOwner()->GetPawn()) // ignore self
		{
			continue;
		}

		if (!Cast<ARCCharacter>(character)->IsAlive()) // ignore dead body
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


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, target);
	if (target)
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString UBTTask_FindTarget::GetStaticDescription() const
{
	return FString();
}
