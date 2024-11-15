// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RCCharacter.h"
#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"
#include "Core/RCGameInstance.h"



ARCCharacter::ARCCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<URCAbilitySystemComponent>(TEXT("AbilityComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	Attributes = CreateDefaultSubobject<URCAttributeSet>(TEXT("Attributes"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	//AudioComponent->SetSound();
}

void ARCCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().ClearTimer(DefWeaponSpawnDelay);
	GetWorld()->GetTimerManager().SetTimer(DefWeaponSpawnDelay, this, &ARCCharacter::SpawnDefaultWeapon, 1.0f, false);

	if (Attributes)
	{
		Attributes->OnHealthChanged.AddDynamic(this, &ARCCharacter::HandleHealthChanged);
	}
	
	if (HasAuthority())	
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(this, this);
			AddStartupGameplayAbilities();
			AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUFunction(this, FName("ActiveGEAdded"));;
			AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUFunction(this, FName("GERemoved"));
		}	

	}

	
	

}

void ARCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentEffectTagsContainer.Num() > 0 && HasAuthority() && IsAlive())
	{
		TArray<FGameplayTag> InOutGameplayTags;
		CurrentEffectTagsContainer.GetGameplayTagArray(InOutGameplayTags);
		float remainigTime = 0.0f;
		float duration = 0.0f;
		for (FGameplayTag tag : CurrentEffectTagsContainer)
		{	
			if (GetCooldownRemainingForTag(tag.GetSingleTagContainer(), remainigTime, duration))
			{
				Client_UpdateRelatedTagCooldown(tag, remainigTime, duration);
			}
		}
	}

}

void ARCCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AddStartupGameplayAbilities();
	}
}

void ARCCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void ARCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARCCharacter::AddStartupGameplayAbilities()
{
	if (AbilitySystemComponent)
	{
		if (GetLocalRole() == ROLE_Authority && !AbilityInitialized)
		{
			for (TSubclassOf<URCGameplayAbility>& startupAbility : GameplayAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
					startupAbility, 1,
					static_cast<int32>(startupAbility.GetDefaultObject()->AbilityInputID),
					this));
			}

			for (TSubclassOf<UGameplayEffect>& effect : PassiveGameplayEffects)
			{
				FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
				EffectContext.AddSourceObject(this);

				FGameplayEffectSpecHandle  NewHandle = AbilitySystemComponent->MakeOutgoingSpec(effect, 1, EffectContext);

				if (NewHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGameplayEffectHandle = 
						AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
				}
			}
			AbilityInitialized = true;
		}

	}
}

void ARCCharacter::Multicast_SetAnimState_Implementation(EALSOverlayState overlay)
{
	SetOverlayState(overlay);
	AimAction(true);
}

void ARCCharacter::Server_LightAttackAction_Implementation(const bool val)
{
	if (HoldWeaponRef)
	{
		HoldWeaponRef->Server_WeaponFire(val);
	}
}


void ARCCharacter::Server_SpawnBaseWeapon_Implementation(TSubclassOf<ABaseWeapon> WeaponClass)
{
	if (WeaponClass)
	{
		CurrentWeaponClass = WeaponClass;
		if (ChildActorComponent && CurrentWeaponClass)
		{
			ChildActorComponent->SetChildActorClass(CurrentWeaponClass);

			if (HeldObjectRoot.Get())
			{
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
				ChildActorComponent->AttachToComponent(HeldObjectRoot.Get(), rules);
			}
			

			HoldWeaponRef = Cast<ABaseWeapon>(ChildActorComponent->GetChildActor());
			if (HoldWeaponRef)
			{
				Multicast_SetAnimState(HoldWeaponRef->WeaponOverlayState);
				HoldWeaponRef->OwnerCharacter = this;
			}

		}


	}
	else
	{
		FString msg = "Invalid weapon class";
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Cyan, *msg);
	}
	
}

void ARCCharacter::Server_DashAction_Implementation(const bool val)
{
	SendInputToAbilities(val, ERCAbilityInputID::Dash);
}


void ARCCharacter::Server_UpdraftAction_Implementation(const bool val)
{
	SendInputToAbilities(val, ERCAbilityInputID::Updraft);
}

void ARCCharacter::KillCharacter()
{
	if (HasAuthority())
	{		
		auto Attrib = GetAttributes();
		if (Attrib)
		{
			Attrib->OnCharacterKilled.Clear();
			Attrib->OnHealthChanged.Clear();			
		}

		RagdollAction();
		if (HoldWeaponRef)
		{
			HoldWeaponRef->Server_WeaponFire(false);
		}
	}
	
}

bool ARCCharacter::IsAlive() const
{
	auto Attrib = GetAttributes();
	if (Attrib)
	{
		return Attrib->GetHealth() > 0.0f;
	}

	return false;
}

UAbilitySystemComponent* ARCCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARCCharacter::HandleDamage(float damageAmount, const FHitResult& hitInfo, const FGameplayTagContainer& damageTags, ARCCharacter* InstigatorCharacter, AActor* damageCauser)
{
	//OnDamage(damageAmount, hitInfo, damageTags, InstigatorCharacter, damageCauser);
}

void ARCCharacter::HandleHealthChanged(float deltaValue, AActor* source)
{
	//OnHealthChanged(deltaValue);
}

void ARCCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARCCharacter, HoldWeaponRef);

}

URCAttributeSet* ARCCharacter::GetAttributes() const
{
	return Attributes;
}

void ARCCharacter::SpawnDefaultWeapon()
{
	Server_SpawnBaseWeapon(DefaultWeaponClass);
}

void ARCCharacter::AttackActionBase(bool val)
{
	
	if (IsLocallyControlled())
	{
		Server_LightAttackAction(val); 		
	}
	
}

void ARCCharacter::DashActionBase(bool val)
{
	if (IsLocallyControlled())
	{
		Server_DashAction(val);
	}
}

void ARCCharacter::UpdraftActionBase(bool val)
{
	if (IsLocallyControlled())
	{
		Server_UpdraftAction(val);
	}
	
}

void ARCCharacter::SendInputToAbilities(bool Pressed, ERCAbilityInputID AbilityInputID)
{
	if (!AbilitySystemComponent) return;

	if (Pressed)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputID));
	}
	else
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityInputID));
	}
	
}

void ARCCharacter::ActiveGEAdded(UAbilitySystemComponent* component, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle)
{
		
	FGameplayTagContainer Container;
	GESpec.GetAllGrantedTags(Container);

	TArray<FGameplayTag> InOutGameplayTags;
	Container.GetGameplayTagArray(InOutGameplayTags);
	for (FGameplayTag tag : InOutGameplayTags)
	{
		if (!CurrentEffectTagsContainer.HasTagExact(tag))
		{
			CurrentEffectTagsContainer.AddTag(tag);
		}
		
	}

}

void ARCCharacter::GERemoved(const FActiveGameplayEffect& GEEffect)
{
	FGameplayTagContainer Container;
	GEEffect.Spec.GetAllGrantedTags(Container);

	TArray<FGameplayTag> InOutGameplayTags;
	Container.GetGameplayTagArray(InOutGameplayTags);
	for (FGameplayTag tag : InOutGameplayTags)
	{
		if (CurrentEffectTagsContainer.HasTagExact(tag))
		{
			CurrentEffectTagsContainer.RemoveTag(tag);
		}		
	}	
}

bool ARCCharacter::GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration)
{
	if (AbilitySystemComponent && CooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray< TPair<float, float> > DurationAndTimeRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}

	return false;
}

void ARCCharacter::Client_UpdateRelatedTagCooldown_Implementation(const FGameplayTag& Tag, const float& renmaining, const float& duration)
{
	if (!CashedHUD)
	{
		if (ARCDeathMatchPC* PC = Cast<ARCDeathMatchPC>(GetController()))
		{
			CashedHUD = Cast<ARCDeathMatchHUD>(PC->GetHUD());

		}
	}
	if (CashedHUD)
	{
		CashedHUD->UpdateTagRelatedCooldown(Tag, renmaining, duration);
	}
	
}
