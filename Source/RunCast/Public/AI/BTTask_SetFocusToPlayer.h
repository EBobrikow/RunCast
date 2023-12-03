// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetFocusToPlayer.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Set Focus to Player"))
class RUNCAST_API UBTTask_SetFocusToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetFocusToPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
};
