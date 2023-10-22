// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/BaseProjectile.h"
#include "Interfaces/DamagebleInterface.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	BaseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = BaseSphere;

	BaseSphere->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHitComponent);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseProjectile::OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
	{
		return;
	}

	IDamagebleInterface* damageble = Cast<IDamagebleInterface>(OtherActor);
	if (damageble)
	{
		damageble->ApplyDamage(ProjectileDamage);
	}
	Multicast_AfterEffect();

	Destroy();
}

void ABaseProjectile::Multicast_AfterEffect_Implementation()
{
	ApplyHitAfterEffect();
}



// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABaseProjectile::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	
//
//}