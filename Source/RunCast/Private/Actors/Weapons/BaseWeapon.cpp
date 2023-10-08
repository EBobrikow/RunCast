// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(DefaultRoot);
	//auto transrofm = WeaponSkeletalMesh->GetRelativeTransform();
	//FVector loc = transrofm.GetTranslation();
	//loc.Z -= 3.0f;
	//transrofm.SetTranslation(loc);
	//WeaponSkeletalMesh->SetRelativeTransform(transrofm);

	SetReplicates(true);
}

void ABaseWeapon::Server_WeaponFire_Implementation()
{
	WeaponFire();
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::WeaponFire()
{
	//if (FireSound)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	//}

	if (WeaponSkeletalMesh && bCanAttack)
	{
		auto animInst = WeaponSkeletalMesh->GetAnimInstance();
		if (animInst && FireMontage)
		{
			float lenth = animInst->Montage_Play(FireMontage);
			UE_LOG(LogTemp, Warning, TEXT("Fire montage lenth = %f"), lenth);
			
		}

		FVector socketLoc = WeaponSkeletalMesh->GetSocketLocation(FName("Launch"));
		auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);
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
				GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, transform);
				
				bCanAttack = false;
				
				GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
				GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ABaseWeapon::CooldownOff, AttackCooldown, false);
			}
			
		}
		
	}

}

void ABaseWeapon::CooldownOff()
{
	bCanAttack = true;
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABaseWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//
//}