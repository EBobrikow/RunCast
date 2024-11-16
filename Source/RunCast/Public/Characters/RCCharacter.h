// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "Actors/Weapons/BaseWeapon.h"
#include "Components/ChildActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemInterface.h"
#include "Components/RCAbilitySystemComponent.h"
#include "Abilities/RCAttributeSet.h"
#include "GameplayEffect.h"
#include "Abilities/RCGameplayAbility.h"
#include "Tools/Globals.h"
#include "RCCharacter.generated.h"



UCLASS()
class RUNCAST_API ARCCharacter : public AALSCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: 

	ARCCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddStartupGameplayAbilities();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	ABaseWeapon* HoldWeaponRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION(Server, Reliable)
	void Server_LightAttackAction(const bool val);

	UFUNCTION(Server, Reliable)
	void Server_DashAction(const bool val);

	UFUNCTION(Server, Reliable)
	void Server_UpdraftAction(const bool val);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetAnimState(EALSOverlayState overlay);

	UFUNCTION(Server, Reliable)
	void Server_SpawnBaseWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void KillCharacter();

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void HandleDamage(float damageAmount, const FHitResult& hitInfo, const struct FGameplayTagContainer& damageTags,
		ARCCharacter* InstigatorCharacter, AActor* damageCauser);

	UFUNCTION()
	virtual void HandleHealthChanged(float deltaValue, AActor* source);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	URCAttributeSet* GetAttributes() const;

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* ChildActorComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseWeapon> CurrentWeaponClass;

	UPROPERTY()
	FTimerHandle DefWeaponSpawnDelay;

	UFUNCTION()
	void SpawnDefaultWeapon();

	virtual void AttackActionBase(bool val) override;

	virtual void DashActionBase(bool val) override;

	virtual void UpdraftActionBase(bool val) override;

	//Abilities

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URCAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URCAttributeSet* Attributes = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<URCGameplayAbility>> GameplayAbilities;

	UPROPERTY()
	bool AbilityInitialized = false;

	UPROPERTY()
	FGameplayTagContainer CurrentEffectTagsContainer;

	UFUNCTION()
	void SendInputToAbilities(bool Pressed, ERCAbilityInputID AbilityInputID);

	UFUNCTION()
	void ActiveGEAdded(UAbilitySystemComponent* component, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle);

	UFUNCTION()
	void GERemoved(const FActiveGameplayEffect& GEEffect);

	UFUNCTION()
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

	UFUNCTION(Client, Unreliable)
	void Client_UpdateRelatedTagCooldown(const FGameplayTag& Tag ,const float& renmaining, const float& duration);

private: 

	UPROPERTY()
	bool TrackDashCooldown = false;

	UPROPERTY()
	class ARCDeathMatchHUD* CashedHUD;

};
