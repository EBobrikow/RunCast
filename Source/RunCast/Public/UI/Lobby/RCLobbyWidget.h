// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ComboBoxString.h"
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


protected:

	UFUNCTION(BlueprintCallable)
	void OnReturnClicked();

	UFUNCTION(BlueprintCallable)
	void OnCreateClicked();

	UFUNCTION(BlueprintCallable)
	void FillComboBoxes();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxPlayers;
};
