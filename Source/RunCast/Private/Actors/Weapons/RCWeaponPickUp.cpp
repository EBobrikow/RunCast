// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RCWeaponPickUp.h"
#include "Characters/RCCharacter.h"

// Sets default values
ARCWeaponPickUp::ARCWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	BaseSphere->SetupAttachment(BaseMesh);
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
	Multicast_DrawSphere();
}

void ARCWeaponPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ARCWeaponPickUp::OnBeginOverlap"));

	ARCCharacter* Char = Cast<ARCCharacter>(OtherActor);
	if (Char)
	{
		Char->Server_SpawnBaseWeapon(WeaponClass);
		//Char->SpawnBaseWeapon(WeaponClass);
		
		/*BaseSphere->OnComponentBeginOverlap.Clear();
	
		GetWorld()->GetTimerManager().ClearTimer(PickUpResetTimer);
		GetWorld()->GetTimerManager().SetTimer(PickUpResetTimer, this, &ARCWeaponPickUp::ResetSpawn, 0.01f, false, ResetTime);*/
	}
}

void ARCWeaponPickUp::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ARCWeaponPickUp::ResetSpawn()
{
}

void ARCWeaponPickUp::Multicast_DrawSphere_Implementation()
{
	DrawDebugSphere(GetWorld(), BaseMesh->GetComponentLocation(), 100.0f, 6, FColor::Cyan);
}

// Called every frame
void ARCWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

