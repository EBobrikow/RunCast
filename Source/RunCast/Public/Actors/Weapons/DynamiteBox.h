// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemInterface.h"
#include "Components/RCAbilitySystemComponent.h"
#include "Abilities/RCAttributeSet.h"
#include "GameplayEffect.h"
#include "DynamiteBox.generated.h"

UCLASS()
class RUNCAST_API ADynamiteBox : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamiteBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamite")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExplosionRadius = 800.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExplosionDamage = 150.0f;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ApplyEffects();

	UFUNCTION()
	void ApplyAbilityDamage(AActor* instigatorCharacter);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> ExplosionDamageEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag CueTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BigBadaBum(); // Just a name joke XD

	UFUNCTION(Server, Reliable)
	void Server_TakeDamage();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AfterEffect();

	//Ability

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URCAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URCAttributeSet* Attributes = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	void AddStartupGameplayAbilities();

	UPROPERTY()
	bool AbilityInitialized = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
