// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_StopAttack.h"
#include "Characters/RCCharacter.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_StopAttack::UBTTask_StopAttack()
{
	NodeName = "Stop Attack";
}

EBTNodeResult::Type UBTTask_StopAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ABaseWeapon* holdWeapon = nullptr;
	ARCCharacter* SelfChar = Cast<ARCCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (SelfChar)
	{
		holdWeapon = SelfChar->HoldWeaponRef;
		if (holdWeapon)
		{
			holdWeapon->SetTargetLocation(FVector::ZeroVector);
			SelfChar->Server_LightAttackAction(false);
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}

FString UBTTask_StopAttack::GetStaticDescription() const
{
	return FString();
}
