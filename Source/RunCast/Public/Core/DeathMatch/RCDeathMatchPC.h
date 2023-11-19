// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Core/RCPlayerController.h"
#include "Characters/RCCharacter.h"
#include "Core/DeathMatch/RCDeathMatchGameState.h"
#include "RCDeathMatchPC.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthStatusUpdate, float, health);

UCLASS()
class RUNCAST_API ARCDeathMatchPC : public ARCPlayerController
{
	GENERATED_BODY()

public: 

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void CreateCharacter();

	UFUNCTION(Server, Reliable)
	void Server_CreateCharacter(TSubclassOf<ARCCharacter> charClass);

	UFUNCTION()
	UClass* GetCharacterClass() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ARCCharacter> DefaultCharacterClass;

protected: 

	virtual void TimeUpdate(int32 Min, int32 Sec) override;

	UFUNCTION(Client, Reliable)
	void Client_Init();

	UFUNCTION()
	void CharacterKilled(ACharacter* killer);

	UFUNCTION()
	void HealthUpdate(float val);

	UFUNCTION(Client, Reliable)
	void Client_UpdateHealthStatus(const float hp);

	UFUNCTION()
	void Restart();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ARCCharacter> CharacterClass;

	UPROPERTY()
	float RestartDelayTime = 3.0f;

	UPROPERTY()
	FTimerHandle RestartDelay;

	
};
