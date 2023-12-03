// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tools/Globals.h"
#include "UI/Common/RCScoreBoard.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FinaleStat.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UFinaleStat : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void Init(TArray<FScoreBoardData> data);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ContinueBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WinnerTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCScoreBoard* BP_ScoreBoard;

protected: 

	UFUNCTION()
	void OnContinueClicked();

};
