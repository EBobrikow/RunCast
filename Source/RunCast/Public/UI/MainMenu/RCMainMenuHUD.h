// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/MainMenu/RCMainMenuWidget.h"
#include "RCMainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget classes")
	TSubclassOf<URCMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	URCMainMenuWidget* MainMenuWidget = nullptr;
	
};
