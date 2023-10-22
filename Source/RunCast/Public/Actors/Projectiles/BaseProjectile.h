// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class RUNCAST_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	USphereComponent* BaseSphere = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	float ProjectileDamage = 10.0f;

	UFUNCTION(BlueprintCallable)
	void OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ApplyHitAfterEffect();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_AfterEffect();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
