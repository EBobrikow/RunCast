// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/EditableText.h"
#include "Components/CircularThrobber.h"
#include "Core/RCGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/MainMenu/RCServerList.h"
#include "UI/Settings/RCSettingsWidget.h"
#include "RCMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SoloGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SearchGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Settings_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCServerList* WB_ServersList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCSettingsWidget* WB_SettingsMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RefreshServerListBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NoAvailableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* ServerListBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* PlayerNameEdText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* ServerNameBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ServerNameEdText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CreateServerBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* LoadingThrobber;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* LoadingThrobber_1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* FadeBorder;

protected:

	UFUNCTION(BlueprintCallable)
	void OnSoloGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnHostGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnSearchGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnSettingsClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnRefreshClicked();

	UFUNCTION(BlueprintCallable)
	void OnCreateServerClicked();

	UFUNCTION()
	void OnListRecieved(TArray<FServerInfo> serverList);

	UFUNCTION(BlueprintCallable)
	void PlayerNameCommited(FString name);

	UFUNCTION()
	void LoadPlayerName();

	UFUNCTION(BlueprintCallable)
	void HideAll();

	UFUNCTION(BlueprintCallable)
	void ButtonSetup();

	UFUNCTION()
	void EnableButtons();

	UPROPERTY()
	URCGameInstance* GameInstancePtr;

	UPROPERTY()
	FTimerHandle DisableButtonsHandler;
};
