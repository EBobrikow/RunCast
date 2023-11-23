// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/Button.h"
#include "StylizedButton.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UStylizedButton : public UButton
{
	GENERATED_BODY()

	UStylizedButton();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
};
