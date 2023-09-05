// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tools/ConnectionManager.h"
#include "Tools/ServerManager.h"
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


	//UE server function to update server status shutdown etc.
#if UE_SERVER

#endif

	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSoloGame;

	

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UServerManager* ServerManager = nullptr;
};
