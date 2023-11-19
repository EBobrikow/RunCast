// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreBoardListEntry.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UScoreBoardListEntry : public UUserWidget
{
	GENERATED_BODY()
	
public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerNameTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KillsTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DeathTxt;
};
