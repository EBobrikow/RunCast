// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Core/Lobby/RCLobbyGameState.h"
#include "RCLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* MatchTypeComboBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* ArenaComboBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* MaxPlayersEdText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ReturnBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CreateBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* MatchPreviewImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* MapPreviewImg;

protected:

	UFUNCTION(BlueprintCallable)
	void OnReturnClicked();

	UFUNCTION(BlueprintCallable)
	void OnCreateClicked();

	UFUNCTION(BlueprintCallable)
	void OnMatchSelectionChanged(FString sItem);

	UFUNCTION(BlueprintCallable)
	void OnMapSelectionChanged(FString sItem);

	UFUNCTION(BlueprintCallable)
	void FillComboBoxes();

	UFUNCTION(BlueprintCallable)
	void SetServerName();

	UFUNCTION()
	void UnlockButton();

	UPROPERTY()
	FTimerHandle ServerNameAwaitTimer;

	UPROPERTY()
	FTimerHandle ButtonUnlockTimer;

	UPROPERTY()
	float AwaitRate = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxPlayers;

private: 

	UPROPERTY()
	TArray<FArenaMapData> mapsInfo;

	UPROPERTY()
	TArray<FArenaMatchData> matchesData;

	UPROPERTY()
	FArenaMapData currentMap;

	UPROPERTY()
	FArenaMatchData currentMatch;
};
