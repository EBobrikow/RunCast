// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Characters/RCCharacter.h"
#include "RCCharacterSlotData.generated.h"


USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UTexture2D> CharacteIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ARCCharacter> CharacterClass;
	
};

UCLASS(Blueprintable, BlueprintType)
class RUNCAST_API URCCharacterSlotData : public UObject
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotData> CharactersData;
};
