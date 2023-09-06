// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "RCSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Buttons
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* VideoSectionSettingBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* AudioSectionSettingBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ApplyAudioChangesBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RetunBtn;

	// Vertical Boxes
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* VideoVerticalBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* AudioVerticalBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* EmptyBox;

	//Sliders
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* MusicVoluemSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* AmbientVoluemSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* EffectsVoluemSlider;

	//Widget switcher
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* SettingsWidgetSwitcher;

protected:

	UFUNCTION(BlueprintCallable)
	void OnVideoSectionClicked();

	UFUNCTION(BlueprintCallable)
	void OnAudioSectionClicked();

	UFUNCTION(BlueprintCallable)
	void OnApplyAudioChangesClicked();

	UFUNCTION(BlueprintCallable)
	void OnReturnClicked();


	UFUNCTION(BlueprintCallable)
	void HideAllSections();
	
};
