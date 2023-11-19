// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Tools/Globals.h"
#include "RCScoreBoard.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCScoreBoard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* ScoreBoardListView;

	UFUNCTION()
	void ConstructList(TArray<FScoreBoardData> listData);

protected: 

	TArray<FScoreBoardData> ScoreData;
};
