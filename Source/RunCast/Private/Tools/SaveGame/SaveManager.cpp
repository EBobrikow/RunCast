// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/SaveGame/SaveManager.h"

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
