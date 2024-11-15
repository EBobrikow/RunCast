// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickUp/RCBasePickUp.h"
#include "Components/SphereComponent.h"
#include "GameplayEffect.h"
#include "RCEffectPickUp.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API ARCEffectPickUp : public ARCBasePickUp
{
	GENERATED_BODY()

public: 

	ARCEffectPickUp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USphereComponent* BaseSphere = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> ApplyedEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void ResetOverlap();
	
};
