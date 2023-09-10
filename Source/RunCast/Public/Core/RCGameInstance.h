// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tools/Server/ConnectionManager.h"
#include "Tools/Server/ServerManager.h"
#include "Tools/SaveGame/SaveManager.h"
#include "GameFramework/GameModeBase.h"
#include "RCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void StartSoloGame();

	UFUNCTION(BlueprintCallable)
	void ExitToMainMenu();

	UFUNCTION(BlueprintCallable)
	UServerManager* GetServerManager();

	UFUNCTION(BlueprintCallable)
	USaveManager* GetSaveManager();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowMainMenu();

	

	UFUNCTION()
	void SetCurrentServerInfo(FCurrentServerInfo servInfo);

	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSoloGame;

	

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UServerManager* ServerManager = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USaveManager* SaveManager = nullptr;

	UPROPERTY()
	FCurrentServerInfo CurrentServerInfo;
};
