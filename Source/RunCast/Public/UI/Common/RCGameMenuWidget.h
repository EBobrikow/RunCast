// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Settings/RCSettingsWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Core/RCGameInstance.h"
#include "RCGameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenu_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Settings_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCSettingsWidget* SettingsMenu;


protected: 

	UFUNCTION(BlueprintCallable)
	void OnMainMenuClicked();

	UFUNCTION(BlueprintCallable)
	void OnSettingsClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitGameClicked();

private: 

	UPROPERTY()
	URCGameInstance* GameInstancePtr;
};
