// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DeathMatch/RCDeathMatchPC.h"
#include "Core/DeathMatch/RCDeathMatchGM.h"
#include "Actors/NetSpawnPoint.h"
#include "Characters/RCCharacter.h"
#include "UI/DeathMatch/RCDeathMatchHUD.h"

void ARCDeathMatchPC::BeginPlay()
{
	Super::BeginPlay();

	CreateCharacter();
}

void ARCDeathMatchPC::CreateCharacter()
{
	if (HasAuthority())
	{
		ARCDeathMatchGM* GM = Cast<ARCDeathMatchGM>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			UClass* pawnClass = GM->GetDefaultCharacterClass();
			if (pawnClass)
			{
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANetSpawnPoint::StaticClass(), FoundActors);
				if (FoundActors.Num() > 0)
				{
					int32 randInd = FMath::RandRange(0, FoundActors.Num()-1);
					FVector loc = FoundActors[randInd]->GetActorLocation();
					UE_LOG(LogTemp, Warning, TEXT("Spawn location: %f, %f, %f"), loc.X, loc.Y, loc.Z);
					FRotator rot = FRotator::ZeroRotator;
					APawn* pawn = GetWorld()->SpawnActor<APawn>(pawnClass, loc, rot);
					if (pawn)
					{
						Possess(pawn);
						if (ARCCharacter* character = Cast<ARCCharacter>(pawn))
						{
							auto hp = character->GetHealthComponent();
							if (hp)
							{
								hp->OnActorKilled.AddDynamic(this, &ARCDeathMatchPC::CharacterKilled);
							}
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ARCDeathMatchPC::CreateCharacter No spawn points was found"));
				}

				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ARCDeathMatchPC::CreateCharacter Invalid pawn class to spawn"));
			}
		}
	}
}

void ARCDeathMatchPC::CharacterKilled()
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		auto hp = character->GetHealthComponent();
		if (hp)
		{
			hp->OnActorKilled.Clear();
		}

		character->RagdollAction();
		character->DisableInput(this);
		//character->EnableInput(this);
		GetWorld()->GetTimerManager().ClearTimer(RestartDelay);
		GetWorld()->GetTimerManager().SetTimer(RestartDelay, this, &ARCDeathMatchPC::Restart, RestartDelayTime, false);
	}
	
}

void ARCDeathMatchPC::Restart()
{
	ARCCharacter* character = Cast<ARCCharacter>(PossessedCharacter);
	if (character)
	{
		UnPossess();
		character->Destroy();
		CreateCharacter();
		ARCDeathMatchHUD* hud = Cast<ARCDeathMatchHUD>(GetHUD());
		if (hud)
		{
			hud->UpdateHealthBar(hud->GetCharacterHP());
		}
	}
}
