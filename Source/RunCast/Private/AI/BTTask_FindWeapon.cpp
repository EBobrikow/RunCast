// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindWeapon.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/PickUp/RCWeaponPickUp.h"
#include "Characters/RCCharacter.h"

UBTTask_FindWeapon::UBTTask_FindWeapon()
{
	NodeName = "Find Weapon";
}

EBTNodeResult::Type UBTTask_FindWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> Weapons;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARCWeaponPickUp::StaticClass(), Weapons);
	FVector selfLoc = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	ARCCharacter* selfChar = Cast<ARCCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	for (AActor* gun : Weapons)
	{
		ARCWeaponPickUp* pickUp = Cast<ARCWeaponPickUp>(gun);
		if (pickUp && selfChar && selfChar->HoldWeaponRef)
		{
			if (FVector::Dist(selfLoc, pickUp->GetActorLocation()) < MaxDistance)
			{
				if (pickUp->WeaponClass != selfChar->HoldWeaponRef->GetClass())
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, pickUp->GetActorLocation());
					return EBTNodeResult::Succeeded;
				}
			}
		}
		
	}


	return EBTNodeResult::Failed;
}

FString UBTTask_FindWeapon::GetStaticDescription() const
{
	return FString();
}
