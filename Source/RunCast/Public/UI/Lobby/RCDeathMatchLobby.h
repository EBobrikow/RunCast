// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Core/Lobby/RCLobbyGameState.h"
#include "Data/RCCharacterSlotData.h"
#include "UI/Common/RCCharacterSelectionGrid.h"
#include "RCDeathMatchLobby.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCDeathMatchLobby : public UUserWidget
{
	GENERATED_BODY()

public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ServerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MatchTypeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MapNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ReadyBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* AddBotBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RemoveBotBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* PlayersListView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCCharacterSelectionGrid* CharacterSelection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URCCharacterSlotData> CharactersSlotsDataClass;

	UFUNCTION()
	void OnAddBotButtonClicked();

	UFUNCTION()
	void OnRemoveBotButtonClicked();

	UFUNCTION()
	void OnReadyButtonClicked();

	UFUNCTION()
	void CreatePlayerList(TArray<FPlayerData> list);

	UFUNCTION()
	void FillServerInfo(FServerInfo info);

	UFUNCTION()
	void CreateSelectionGrid();

	UPROPERTY()
	TArray<FPlayerData> localPlayerList;

	UPROPERTY()
	FTimerHandle FillInfoTimer;

	UFUNCTION()
	void FillInfo();
	
};
