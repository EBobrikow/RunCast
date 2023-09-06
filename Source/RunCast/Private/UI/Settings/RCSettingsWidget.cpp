// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Settings/RCSettingsWidget.h"

void URCSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (VideoSectionSettingBtn)
	{
		VideoSectionSettingBtn->OnClicked.Clear();
		VideoSectionSettingBtn->OnClicked.AddUniqueDynamic(this, &URCSettingsWidget::OnVideoSectionClicked);
	}

	if (AudioSectionSettingBtn)
	{
		AudioSectionSettingBtn->OnClicked.Clear();
		AudioSectionSettingBtn->OnClicked.AddUniqueDynamic(this, &URCSettingsWidget::OnAudioSectionClicked);
	}

	if (ApplyAudioChangesBtn)
	{
		ApplyAudioChangesBtn->OnClicked.Clear();
		ApplyAudioChangesBtn->OnClicked.AddUniqueDynamic(this, &URCSettingsWidget::OnApplyAudioChangesClicked);
	}

	if (RetunBtn)
	{
		RetunBtn->OnClicked.Clear();
		RetunBtn->OnClicked.AddUniqueDynamic(this, &URCSettingsWidget::OnReturnClicked);
	}

	HideAllSections();
}

void URCSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URCSettingsWidget::OnVideoSectionClicked()
{
	if (SettingsWidgetSwitcher)
	{
		SettingsWidgetSwitcher->SetActiveWidgetIndex(2);
	}
}

void URCSettingsWidget::OnAudioSectionClicked()
{
	if (SettingsWidgetSwitcher)
	{
		SettingsWidgetSwitcher->SetActiveWidgetIndex(1);
	}
}

void URCSettingsWidget::OnApplyAudioChangesClicked()
{
}

void URCSettingsWidget::OnReturnClicked()
{
	HideAllSections();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void URCSettingsWidget::HideAllSections()
{
	if (SettingsWidgetSwitcher)
	{
		SettingsWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}
