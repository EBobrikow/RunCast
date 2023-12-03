// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/SaveGame/SaveManager.h"

void USaveManager::Init()
{
    if (!IsSaveExist())
    {
        URCSaveGame* save =  CreateSaveGameObj();
        save->AmbientVoluem = 0.5f;
        save->MusicVoluem = 0.5f;
        save->EffectsVoluem = 0.5f;
        save->PlayerName = "Player";

        save->Graphics = ESettingsQuality::High;
        save->Shadow = ESettingsQuality::High;
        save->Aliasing = ESettingsQuality::High;
        save->PostProcessing = ESettingsQuality::High;
        save->ViewDistance = ESettingsQuality::High;
        save->Texture = ESettingsQuality::High;
        save->Effects = ESettingsQuality::High;


        SaveGameObject(save);
    }
}

URCSaveGame* USaveManager::CreateSaveGameObj()
{
    return NewObject<URCSaveGame>(this);
}

bool USaveManager::IsSaveExist() const
{
    return UGameplayStatics::DoesSaveGameExist(SaveSlotName,0);
}

URCSaveGame* USaveManager::LoadGameObject() const
{
    return Cast<URCSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName,0));
}

void USaveManager::SaveGameObject(USaveGame* saveObj) const
{
    UGameplayStatics::SaveGameToSlot(saveObj, SaveSlotName, 0);
}
