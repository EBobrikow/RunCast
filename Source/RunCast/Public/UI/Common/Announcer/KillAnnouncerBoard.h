// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
//#include "Tools/Globals.h"
#include "UI/Common/Announcer/KillAnnouncerDataContainer.h"
#include "KillAnnouncerBoard.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UKillAnnouncerBoard : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* AnnouncerListView;

	UFUNCTION()
	void AddKillAnnounce(FString killerName, EWeaponIconType weaponIconType, FString victimName);

	UFUNCTION()
	void RemoveItem(UObject* itemObj);

	
};
