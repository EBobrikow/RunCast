// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: MaxHealth(100.0f)
	, CurrentHealth(100.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}



void UHealthComponent::Multicast_DoDamage_Implementation(const float dmg, ACharacter* instigator)
{
	if (CanTakeDamage)
	{
		CurrentHealth -= dmg;
		if (OnHealthUpdate.IsBound())
		{
			OnHealthUpdate.Broadcast(CurrentHealth);
		}

		if (CurrentHealth < 0)
		{
			CanTakeDamage = false;
			if (OnActorKilled.IsBound())
			{
				OnActorKilled.Broadcast(instigator);
			}
		}
		
	}
	
}


float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = 100.0f;
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//CanTakeDamage = CurrentHealth >= 1.0f;
	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);

}