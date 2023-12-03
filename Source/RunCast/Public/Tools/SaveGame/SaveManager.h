// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Tools/SaveGame/RCSaveGame.h"
#include "SaveManager.generated.h"




UCLASS()
class RUNCAST_API USaveManager : public UObject
{
	GENERATED_BODY()

	const FString SaveSlotName = TEXT("SettingsSave");

public:

	UFUNCTION()
	void Init();

	UFUNCTION()
	URCSaveGame* CreateSaveGameObj();

	UFUNCTION()
	bool IsSaveExist() const;

	UFUNCTION()
	void SaveGameObject(USaveGame* saveObj) const;

	UFUNCTION()
	URCSaveGame* LoadGameObject() const;
};
