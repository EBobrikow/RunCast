// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Core/RCGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/RCServerList.h"
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
	UButton* ExitGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URCServerList* WB_ServersList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RefreshServerListBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NoAvailableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* ServerListOverlay;

protected:

	UFUNCTION(BlueprintCallable)
	void OnSoloGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnHostGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnSearchGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnRefreshClicked();

	UFUNCTION()
	void OnListRecieved(TArray<FServerInfo> serverList);


	UPROPERTY()
	URCGameInstance* GameInstancePtr;
};
