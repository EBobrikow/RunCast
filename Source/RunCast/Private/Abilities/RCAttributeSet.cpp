// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RCAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Characters/RCCharacter.h"

URCAttributeSet::URCAttributeSet()
{
}

void URCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URCAttributeSet, Health);
	DOREPLIFETIME(URCAttributeSet, MaxHealth);
}

void URCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& sourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float delta = 0.0f;

	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		delta = Data.EvaluatedData.Magnitude;

		AActor* targetActor = nullptr;

		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			targetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		}

		if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			UE_LOG(LogTemp, Warning, TEXT("Health update to %s, health = %f, delta = %f"), *GetOuter()->GetName(), GetHealth(), delta);
			float clampVal = FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth());
			SetHealth(clampVal);

			if (OnHealthChanged.IsBound())
			{
				OnHealthChanged.Broadcast(GetHealth(), delta > 0.0f ? nullptr : source->GetOwnerActor());
			}
			float currHealth = GetHealth();
			if (FMath::IsNearlyZero(GetHealth(), 0.001f) && source->GetOwnerActor())
			{
				if (OnCharacterKilled.IsBound())
				{
					OnCharacterKilled.Broadcast(Cast<ACharacter>(source->GetOwnerActor()));
				}
			}

		}
	}

	

}

void URCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void URCAttributeSet::OnRep_Health(const FGameplayAttributeData& oldVal)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URCAttributeSet, Health, oldVal);
}

void URCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldVal)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URCAttributeSet, MaxHealth, oldVal);
}

void URCAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const
{
	/*UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		const float currentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.0f) ? (currentValue * NewMaxValue / CurrentMaxValue) - currentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}*/

}
