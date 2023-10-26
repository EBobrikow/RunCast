// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate,float,Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNCAST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(Server, Reliable)
	void Multicast_DoDamage(const float dmg);


	UPROPERTY()
	FOnActorKilled OnActorKilled;

	UPROPERTY()
	FOnHealthUpdate OnHealthUpdate;

	float GetCurrentHealth() const;

	float GetMaxHealth() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	float MaxHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
private: 

	UPROPERTY()
	bool CanTakeDamage = true;
};
