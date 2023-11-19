// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RCWeaponPickUp.h"
#include "Characters/RCCharacter.h"

// Sets default values
ARCWeaponPickUp::ARCWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	USceneComponent* defRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defRoot"));
	RootComponent = defRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetIsReplicated(true);
	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	BaseSphere->SetupAttachment(BaseMesh);
	if (BaseSphere)
	{
		BaseSphere->SetSphereRadius(100.0f);
		BaseSphere->OnComponentBeginOverlap.AddDynamic(this, &ARCWeaponPickUp::OnBeginOverlap);
	}
}

void ARCWeaponPickUp::ResetOverlap()
{
	if (BaseSphere)
	{
		BaseSphere->OnComponentBeginOverlap.Clear();
	}
}

// Called when the game starts or when spawned
void ARCWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
}

void ARCWeaponPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ARCWeaponPickUp::OnBeginOverlap"));

	ARCCharacter* Char = Cast<ARCCharacter>(OtherActor);
	if (Char)
	{
		ResetOverlap();
		Char->Server_SpawnBaseWeapon(WeaponClass);
		if (OnPickupDelegate.IsBound())
		{
			OnPickupDelegate.Broadcast();
		}
	}
}



// Called every frame
void ARCWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

