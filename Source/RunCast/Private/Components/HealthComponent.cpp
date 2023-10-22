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

void UHealthComponent::Multicast_DoDamage(const float dmg)
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
			if (OnActorKilled.IsBound())
			{
				OnActorKilled.Broadcast();
			}
		}
		
	}
	
}


float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CanTakeDamage = CurrentHealth > 0;
	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);

}