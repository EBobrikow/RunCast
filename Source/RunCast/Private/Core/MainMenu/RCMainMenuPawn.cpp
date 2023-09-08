// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainMenu/RCMainMenuPawn.h"

// Sets default values
ARCMainMenuPawn::ARCMainMenuPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARCMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCMainMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCMainMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

