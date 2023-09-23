// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Core/Lobby/RCLobbyGameState.h"
#include "UI/Lobby/RCLobbyWidget.h"
#include "UI/Lobby/RCDeathMatchLobby.h"
#include "RCLobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCLobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public: 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget classes")
	TSubclassOf<URCLobbyWidget> LobbyEntranceWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget classes")
	TSubclassOf<URCDeathMatchLobby> DeathMatchLobbyWidgetClass;

protected: 

	UFUNCTION()
	void CreateWidgetByLobbyState(ELobbyState state);

	UFUNCTION()
	void DelayDeathMatchLobbyCreation();

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY()
	UUserWidget* PreviosWidget;

	UPROPERTY()
	FTimerHandle DeathMatchDelayTimer;

	UFUNCTION()
	void CreateWidgetByClass(TSubclassOf<UUserWidget> widgetClass);
};
