// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DamagebleInterface.h"
#include "Net/UnrealNetwork.h"
#include "DynamiteBox.generated.h"

UCLASS()
class RUNCAST_API ADynamiteBox : public AActor, public IDamagebleInterface
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

	virtual void ApplyDamage(float dmg) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BigBadaBum(); // Just a name joke XD

	UFUNCTION(Server, Reliable)
	void Server_TakeDamage();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AfterEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
