// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RCWeaponPickUp.h"

// Sets default values
ARCWeaponPickUp::ARCWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (BaseSphere)
	{
		BaseSphere->SetSphereRadius(100.0f);
		BaseSphere->OnComponentBeginOverlap.AddDynamic(this, &ARCWeaponPickUp::OnBeginOverlap);
		BaseSphere->OnComponentEndOverlap.AddDynamic(this, &ARCWeaponPickUp::OnEndOverlap);
	}
}

// Called when the game starts or when spawned
void ARCWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARCWeaponPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ARCWeaponPickUp::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ARCWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

