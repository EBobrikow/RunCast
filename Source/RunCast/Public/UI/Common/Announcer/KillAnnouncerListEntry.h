// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Tools/Globals.h"

#include "KillAnnouncerListEntry.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UKillAnnouncerListEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KillerNameTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* WeaponIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* VictimNameTxt;

	UFUNCTION(BlueprintCallable)
	void SetListEntryData(UObject* dataObject);



protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponIconType, UTexture2D* > IconsMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ItemLifeTime = 2.0f;

private: 

	UPROPERTY()
	UObject* CashedDataContainer = nullptr;

	UPROPERTY()
	FTimerHandle LifeTimerHandle;

	UFUNCTION()
	void LifeTimeEnd();
	
};
