// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lobby/RCLobbyPawn.h"

// Sets default values
ARCLobbyPawn::ARCLobbyPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARCLobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCLobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCLobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

