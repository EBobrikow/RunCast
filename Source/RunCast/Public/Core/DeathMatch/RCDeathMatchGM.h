// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RCGameMode.h"
#include "RCDeathMatchGM.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCDeathMatchGM : public ARCGameMode
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<APawn> GetDefaultCharacterClass() const;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character classes")
	TSubclassOf<APawn> DefaultCharacterClass;
};
