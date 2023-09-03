// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Core/RCGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SoloGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SearchGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGame_Btn;

protected:

	UFUNCTION(BlueprintCallable)
	void OnSoloGamePressed();

	UFUNCTION(BlueprintCallable)
	void OnHostGamePressed();

	UFUNCTION(BlueprintCallable)
	void OnSearchGamePressed();

	UFUNCTION(BlueprintCallable)
	void OnExitGamePressed();


	UPROPERTY()
	URCGameInstance* GameInstancePtr;
};
