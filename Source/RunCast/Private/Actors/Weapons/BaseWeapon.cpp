// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/RCCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(DefaultRoot);
	WeaponSkeletalMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

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

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickFire();
}

void ABaseWeapon::WeaponFire(bool val)
{
	bCanAttack = val;
	//TickFire();
	/*if (WeaponSkeletalMesh && bCooldown && bCanAttack)
	{
		Multicast_PlayMontage(FireMontage);


		auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		ARCCharacter* character = Cast<ARCCharacter>(OwnerCharacter);
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
			FRotator finaleRot = UKismetMathLibrary::FindLookAtRotation(socketLoc, hitEnd);

			FTransform transform = UKismetMathLibrary::MakeTransform(socketLoc, finaleRot);
			if (ProjectileClass)
			{
				auto bullet = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, transform);
				bullet->SetOwnerCharacter(character);
				bullet->SetReplicates(true);
				
				bCooldown = false;
				
				GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
				GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ABaseWeapon::CooldownOff, AttackCooldown, false);
			}
			
		}
		
	}*/

}

void ABaseWeapon::CooldownOff()
{
	bCooldown = true;

}

void ABaseWeapon::TickFire()
{
	if (!bCanAttack)
	{
		return;
	}

	if (WeaponSkeletalMesh && bCooldown)
	{
		Multicast_PlayMontage(FireMontage);


		auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		ARCCharacter* character = Cast<ARCCharacter>(OwnerCharacter);
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
			FRotator finaleRot = UKismetMathLibrary::FindLookAtRotation(socketLoc, hitEnd);

			FTransform transform = UKismetMathLibrary::MakeTransform(socketLoc, finaleRot);
			if (ProjectileClass)
			{
				auto bullet = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, transform);
				bullet->SetOwnerCharacter(character);
				bullet->SetReplicates(true);

				bCooldown = false;

				GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
				GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ABaseWeapon::CooldownOff, AttackCooldown, false);
			}

		}

	}
}



