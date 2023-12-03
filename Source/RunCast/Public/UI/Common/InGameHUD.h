// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Common/RCGameMenuWidget.h"
#include "UI/Common/RCScoreBoard.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ShowGameMenu(APlayerController* pc);

	UFUNCTION()
	void ShowScoreBoard();

	UFUNCTION()
	void HideScoreBoard();

	UFUNCTION()
	void UpdateScoreBoardData(TArray<FScoreBoardData> dataList);


protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCGameMenuWidget> GameMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCScoreBoard> ScoreBoardWidgetClass;

	UPROPERTY()
	URCGameMenuWidget* MenuWidget;

	UPROPERTY()
	URCScoreBoard* ScoreBoardWidget;


	UFUNCTION()
	void CreateMenuWidget();

	UFUNCTION()
	void CreateScoreBoardWidget();

	virtual void GameMenuOpened(bool val);
	
};
