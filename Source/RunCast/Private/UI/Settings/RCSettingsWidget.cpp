// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Settings/RCSettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Core/RCGameInstance.h"
#include "Tools/SaveGame/RCSaveGame.h"


void URCSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SaveManager = Cast<URCGameInstance>(UGameplayStatics::GetGameInstance(this))->GetSaveManager();

	SetupButtonsEvents();
	SetupSlidersEvents();
	HideAllSections();
	SetupAudioFromSave();
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
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
		}
		else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}
		
		
		if (MusicVoluemSlider)
		{
			saveGame->MusicVoluem = MusicVoluemSlider->GetValue();
			
		}
		if (AmbientVoluemSlider)
		{
			saveGame->AmbientVoluem = AmbientVoluemSlider->GetValue();
			
		}
		if (EffectsVoluemSlider)
		{
			saveGame->EffectsVoluem = EffectsVoluemSlider->GetValue();
			
		}
		SaveManager->SaveGameObject(saveGame);

		saveGame = SaveManager->LoadGameObject();
		SetMusicSoundVolume(saveGame->MusicVoluem);
		SetAmbientSoundVolume(saveGame->AmbientVoluem);
		SetEffectsSoundVolume(saveGame->EffectsVoluem);
	}
}

void URCSettingsWidget::OnReturnClicked()
{
	HideAllSections();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void URCSettingsWidget::OnMusicVoluemChanged(float volume)
{
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
		}
		else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}

		if (MusicVoluemSlider)
		{
			saveGame->MusicVoluem = volume;
			SetMusicSoundVolume(saveGame->MusicVoluem);
		}
		
		SaveManager->SaveGameObject(saveGame);
	}
}

void URCSettingsWidget::OnAmbientVoluemChanged(float volume)
{
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
		}
		else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}

		if (AmbientVoluemSlider)
		{
			saveGame->AmbientVoluem = volume;
			SetAmbientSoundVolume(saveGame->AmbientVoluem);
		}

		SaveManager->SaveGameObject(saveGame);
	}
}

void URCSettingsWidget::OnEffectsVoluemChanged(float volume)
{
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
		}
		else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}

		if (EffectsVoluemSlider)
		{
			saveGame->EffectsVoluem = volume;
			SetEffectsSoundVolume(saveGame->EffectsVoluem);
		}

		SaveManager->SaveGameObject(saveGame);
	}
}

void URCSettingsWidget::HideAllSections()
{
	if (SettingsWidgetSwitcher)
	{
		SettingsWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void URCSettingsWidget::SetupButtonsEvents()
{
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
}

void URCSettingsWidget::SetupSlidersEvents()
{
	/*if (SoundMix)
	{
		UGameplayStatics::SetBaseSoundMix(this, SoundMix);
	}*/

	if (MusicVoluemSlider)
	{
		MusicVoluemSlider->OnValueChanged.Clear();
		MusicVoluemSlider->OnValueChanged.AddUniqueDynamic(this, &URCSettingsWidget::OnMusicVoluemChanged);
	}

	if (AmbientVoluemSlider)
	{
		AmbientVoluemSlider->OnValueChanged.Clear();
		AmbientVoluemSlider->OnValueChanged.AddUniqueDynamic(this, &URCSettingsWidget::OnAmbientVoluemChanged);
	}

	if (EffectsVoluemSlider)
	{
		EffectsVoluemSlider->OnValueChanged.Clear();
		EffectsVoluemSlider->OnValueChanged.AddUniqueDynamic(this, &URCSettingsWidget::OnEffectsVoluemChanged);
	}
	
}

void URCSettingsWidget::SetupAudioFromSave()
{
	if (SaveManager && SaveManager->IsSaveExist())
	{
		URCSaveGame* saveGame = SaveManager->LoadGameObject();
		if (MusicVoluemSlider)
		{
			MusicVoluemSlider->SetValue(saveGame->MusicVoluem);
			SetMusicSoundVolume(saveGame->MusicVoluem);
		}
		if (AmbientVoluemSlider)
		{
			AmbientVoluemSlider->SetValue(saveGame->AmbientVoluem);
			SetAmbientSoundVolume(saveGame->AmbientVoluem);
		}
		if (EffectsVoluemSlider)
		{
			EffectsVoluemSlider->SetValue(saveGame->EffectsVoluem);
			SetEffectsSoundVolume(saveGame->EffectsVoluem);
		}
	}
}
