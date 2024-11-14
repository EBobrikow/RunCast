// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/RCCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameplayTagsManager.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(DefaultRoot);
	WeaponSkeletalMesh->SetIsReplicated(true);
	WeaponSkeletalMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	AbilitySystemComponent = CreateDefaultSubobject<URCAbilitySystemComponent>(TEXT("AbilityComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	SetReplicates(true);
}

void ABaseWeapon::Server_WeaponFire_Implementation(bool val)
{
	WeaponFire(val);
}

void ABaseWeapon::Multicast_PlayMontage_Implementation(UAnimMontage* montage)
{
	if (WeaponSkeletalMesh)
	{
		auto animInst = WeaponSkeletalMesh->GetAnimInstance();
		if (animInst && montage)
		{
			float lenth = animInst->Montage_Play(montage);
			UE_LOG(LogTemp, Warning, TEXT("Fire montage lenth = %f"), lenth);

		}
	}
	
}

void ABaseWeapon::SetTargetLocation(FVector loc)
{
	TargetLocation = loc;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	TargetLocation = FVector::ZeroVector;

	if (AbilitySystemComponent && HasAuthority())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
	
}

void ABaseWeapon::FireAction()
{
	if (!OwnerCharacter) return;

	ARCCharacter* character = Cast<ARCCharacter>(OwnerCharacter);
	if (!bCanAttack || !character->IsAlive()) return;
	

	if (WeaponSkeletalMesh)
	{
		Multicast_PlayMontage(FireMontage);


		auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

		if (character)
		{
			APlayerController* PC = Cast<APlayerController>(character->Controller);
			if (PC)
			{
				cameraManager = PC->PlayerCameraManager;
			}
		}

		FVector socketLoc = WeaponSkeletalMesh->GetSocketLocation(FName("Launch"));
		if (cameraManager)
		{
			FRotator cameraRot = cameraManager->GetCameraRotation();
			FVector cameraLoc = cameraManager->GetCameraLocation();
			FVector forwardVec = cameraRot.Vector();
			forwardVec *= 25000;
			FVector end = cameraLoc + forwardVec;
			FHitResult OutHit;
			TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Visibility;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			bool hit = GetWorld()->LineTraceSingleByChannel(OutHit, cameraLoc, end, TraceChannelProperty, QueryParams);
			FVector hitEnd = hit ? OutHit.ImpactPoint : OutHit.TraceEnd;

			if (TargetLocation != FVector::ZeroVector) //AI targeting
			{
				hitEnd = TargetLocation;
			}
			FRotator finaleRot = UKismetMathLibrary::FindLookAtRotation(socketLoc, hitEnd);
			FTransform transform = UKismetMathLibrary::MakeTransform(socketLoc, finaleRot);
			if (ProjectileClass)
			{
				auto bullet = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, transform);
				bullet->SetOwnerCharacter(character);
				bullet->SetReplicates(true);
			}

		}

	}
}

void ABaseWeapon::AddStartupGameplayAbilities()
{
	if (AbilitySystemComponent)
	{
		if (GetLocalRole() == ROLE_Authority && !AbilityInitialized && PrimaryAbility)
		{
			
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				PrimaryAbility, 1,
				static_cast<int32>(PrimaryAbility.GetDefaultObject()->AbilityInputID),
				this));
			
			AbilityInitialized = true;
		}

	}
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AbilityTickFire();
}

void ABaseWeapon::WeaponFire(bool val)
{
	bCanAttack = val;
}

UAbilitySystemComponent* ABaseWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseWeapon::AbilityTickFire()
{
	if (bCanAttack && AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(PrimaryAbility);
	}
}



