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

	ConstructComboBoxes();
	SetupVideoFromSave();
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
		/*else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}*/
		
		
		
	}
}

void URCSettingsWidget::OnReturnClicked()
{
	HideAllSections();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void URCSettingsWidget::OnApplyVideoChangesClicked()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetGraphicsCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetShadowCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetAliasingCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetPostProcessCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetViewDistanceCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetTextureCommand());
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), GetEffectsCommand());

	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();

			saveGame->Graphics = StringToEnum(GraphicsCombo->GetSelectedOption());
			saveGame->Shadow = StringToEnum(ShadowsCombo->GetSelectedOption());
			saveGame->Aliasing = StringToEnum(AliasingCombo->GetSelectedOption());
			saveGame->PostProcessing = StringToEnum(PostProcessCombo->GetSelectedOption());
			saveGame->ViewDistance = StringToEnum(ViewDistanceCombo->GetSelectedOption());
			saveGame->Texture = StringToEnum(TextureCombo->GetSelectedOption());
			saveGame->Effects = StringToEnum(EffectsCombo->GetSelectedOption());

			SaveManager->SaveGameObject(saveGame);
		}
	}

}

void URCSettingsWidget::OnMusicVoluemChanged(float volume)
{
	if (SaveManager)
	{
		URCSaveGame* saveGame = nullptr;
		if (SaveManager->IsSaveExist())
		{
			saveGame = SaveManager->LoadGameObject();
			if (MusicVoluemSlider)
			{
				saveGame->MusicVoluem = volume;
				SetMusicSoundVolume(saveGame->MusicVoluem);
			}

			SaveManager->SaveGameObject(saveGame);
		}
	/*	else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}*/

		
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
			if (AmbientVoluemSlider)
			{
				saveGame->AmbientVoluem = volume;
				SetAmbientSoundVolume(saveGame->AmbientVoluem);
			}

			SaveManager->SaveGameObject(saveGame);
		}
		/*else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}*/

	
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
			if (EffectsVoluemSlider)
			{
				saveGame->EffectsVoluem = volume;
				SetEffectsSoundVolume(saveGame->EffectsVoluem);
			}

			SaveManager->SaveGameObject(saveGame);
		}
		/*else
		{
			saveGame = SaveManager->CreateSaveGameObj();
		}*/

		
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

	if (ApplyVideoChangesBtn)
	{
		ApplyVideoChangesBtn->OnClicked.Clear();
		ApplyVideoChangesBtn->OnClicked.AddUniqueDynamic(this, &URCSettingsWidget::OnApplyVideoChangesClicked);
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

void URCSettingsWidget::ConstructComboBoxes()
{
	if (GraphicsCombo)
	{
		FillCombo(GraphicsCombo);
	}

	if (ShadowsCombo)
	{
		FillCombo(ShadowsCombo);
	}

	if (AliasingCombo)
	{
		FillCombo(AliasingCombo);
	}

	if (PostProcessCombo)
	{
		FillCombo(PostProcessCombo);
	}

	if (ViewDistanceCombo)
	{
		FillCombo(ViewDistanceCombo);
	}

	if (TextureCombo)
	{
		FillCombo(TextureCombo);
	}

	if (EffectsCombo)
	{
		FillCombo(EffectsCombo);
	}
	
}

void URCSettingsWidget::SetupVideoFromSave()
{
	if (SaveManager && SaveManager->IsSaveExist())
	{
		URCSaveGame* saveGame = SaveManager->LoadGameObject();
		
		if (GraphicsCombo)
		{
			GraphicsCombo->SetSelectedOption(EnumToString(saveGame->Graphics));
		}

		if (ShadowsCombo)
		{
			ShadowsCombo->SetSelectedOption(EnumToString(saveGame->Shadow));
		}

		if (AliasingCombo)
		{
			AliasingCombo->SetSelectedOption(EnumToString(saveGame->Aliasing));
		}

		if (PostProcessCombo)
		{
			PostProcessCombo->SetSelectedOption(EnumToString(saveGame->PostProcessing));
		}

		if (ViewDistanceCombo)
		{
			ViewDistanceCombo->SetSelectedOption(EnumToString(saveGame->ViewDistance));
		}

		if (TextureCombo)
		{
			TextureCombo->SetSelectedOption(EnumToString(saveGame->Texture));
		}

		if (EffectsCombo)
		{
			EffectsCombo->SetSelectedOption(EnumToString(saveGame->Effects));
		}

		OnApplyVideoChangesClicked();
	}
}

FString URCSettingsWidget::EnumToString(ESettingsQuality val)
{
	switch (val)
	{
	case ESettingsQuality::Low:
		return "Low";
		break;
	case ESettingsQuality::Medium:
		return "Medium";
		break;
	case ESettingsQuality::High:
		return "High";
		break;
	case ESettingsQuality::Ultra:
		return "Ultra";
		break;
	default:
		break;
	}

	return "Medium";
}

ESettingsQuality URCSettingsWidget::StringToEnum(const FString& val)
{
	if (val == "Low")
	{
		return ESettingsQuality::Low;
	}
	else if (val == "Medium")
	{
		return ESettingsQuality::Medium;
	}
	else if (val == "High")
	{
		return ESettingsQuality::High;
	}
	else if (val == "Ultra")
	{
		return ESettingsQuality::Ultra;
	}

	return ESettingsQuality::Medium;
}

void URCSettingsWidget::FillCombo(UComboBoxString* combo)
{
	if (combo)
	{
		combo->AddOption(EnumToString(ESettingsQuality::Low));
		combo->AddOption(EnumToString(ESettingsQuality::Medium));
		combo->AddOption(EnumToString(ESettingsQuality::High));
		combo->AddOption(EnumToString(ESettingsQuality::Ultra));

		combo->SetSelectedOption(EnumToString(ESettingsQuality::Medium));
	}
	
}

FString URCSettingsWidget::GetGraphicsCommand()
{
	if (GraphicsCombo)
	{
		FString option = GraphicsCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "r.ScreenPercentage 25";
			break;
		case ESettingsQuality::Medium:
			return "r.ScreenPercentage 50";
			break;
		case ESettingsQuality::High:
			return "r.ScreenPercentage 75";
			break;
		case ESettingsQuality::Ultra:
			return "r.ScreenPercentage 100";
			break;
		default:
			break;
		}

	}
	return FString();
}

FString URCSettingsWidget::GetShadowCommand()
{
	if (ShadowsCombo)
	{
		FString option = ShadowsCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "sg.ShadowQuality 0";
			break;
		case ESettingsQuality::Medium:
			return "sg.ShadowQuality 1";
			break;
		case ESettingsQuality::High:
			return "sg.ShadowQuality 2";
			break;
		case ESettingsQuality::Ultra:
			return "sg.ShadowQuality 3";
			break;
		default:
			break;
		}

	}
	return FString();
}

FString URCSettingsWidget::GetAliasingCommand()
{
	if (AliasingCombo)
	{
		FString option = AliasingCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "r.PostProcessAAQuality 0";
			break;
		case ESettingsQuality::Medium:
			return "r.PostProcessAAQuality 2";
			break;
		case ESettingsQuality::High:
			return "r.PostProcessAAQuality 4";
			break;
		case ESettingsQuality::Ultra:
			return "r.PostProcessAAQuality 6";
			break;
		default:
			break;
		}

	}
	return FString();
}

FString URCSettingsWidget::GetPostProcessCommand()
{
	if (PostProcessCombo)
	{
		FString option = PostProcessCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "sg.PostProcessQuality 0";
			break;
		case ESettingsQuality::Medium:
			return "sg.PostProcessQuality 1";
			break;
		case ESettingsQuality::High:
			return "sg.PostProcessQuality 2";
			break;
		case ESettingsQuality::Ultra:
			return "sg.PostProcessQuality 3";
			break;
		default:
			break;
		}

	}

	return FString();
}

FString URCSettingsWidget::GetViewDistanceCommand()
{
	if (ViewDistanceCombo)
	{
		FString option = ViewDistanceCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "r.ViewDistanceScale 0.3";
			break;
		case ESettingsQuality::Medium:
			return "r.ViewDistanceScale 0.5";
			break;
		case ESettingsQuality::High:
			return "r.ViewDistanceScale 0.7";
			break;
		case ESettingsQuality::Ultra:
			return "r.ViewDistanceScale 1.0";
			break;
		default:
			break;
		}

	}
	return FString();
}

FString URCSettingsWidget::GetTextureCommand()
{
	if (TextureCombo)
	{
		FString option = TextureCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "sg.TextureQuality 0";
			break;
		case ESettingsQuality::Medium:
			return "sg.TextureQuality 1";
			break;
		case ESettingsQuality::High:
			return "sg.TextureQuality 2";
			break;
		case ESettingsQuality::Ultra:
			return "sg.TextureQuality 3";
			break;
		default:
			break;
		}

	}
	return FString();
}

FString URCSettingsWidget::GetEffectsCommand()
{
	if (EffectsCombo)
	{
		FString option = EffectsCombo->GetSelectedOption();
		ESettingsQuality quality = StringToEnum(option);

		switch (quality)
		{
		case ESettingsQuality::Low:
			return "sg.EffectsQuality 0";
			break;
		case ESettingsQuality::Medium:
			return "sg.EffectsQuality 1";
			break;
		case ESettingsQuality::High:
			return "sg.EffectsQuality 2";
			break;
		case ESettingsQuality::Ultra:
			return "sg.EffectsQuality 3";
			break;
		default:
			break;
		}

	}
	return FString();
}
