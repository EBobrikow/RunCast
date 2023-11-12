// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RCGameState.generated.h"




UCLASS()
class RUNCAST_API ARCGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

protected: 


};
