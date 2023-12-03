// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AttackTarget.h"
#include "Characters/RCCharacter.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = "Attack Target";
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		}
		
	}
	

	UObject* target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	if (target)
	{
		ARCCharacter* targetChar = Cast<ARCCharacter>(target);
		if (targetChar && holdWeapon)
		{
			
			holdWeapon->SetTargetLocation(targetChar->GetActorLocation());
			SelfChar->Server_LightAttackAction(true);
			return EBTNodeResult::Succeeded;
		}

	}


	return EBTNodeResult::Failed;
}

FString UBTTask_AttackTarget::GetStaticDescription() const
{
	return FString();
}
