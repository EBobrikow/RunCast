// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Common/RCGameMenuWidget.h"
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

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCGameMenuWidget> GameMenuWidgetClass;

	UPROPERTY()
	URCGameMenuWidget* MenuWidget;


	UFUNCTION()
	void CreateMenuWidget();
	
};
