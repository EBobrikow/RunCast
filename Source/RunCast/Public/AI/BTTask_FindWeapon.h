// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindWeapon.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UBTTask_FindWeapon : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindWeapon();

	UPROPERTY(Category = Navigation, EditAnywhere, meta = (ClampMin = 1))
	float MaxDistance = 1000.0f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
};
