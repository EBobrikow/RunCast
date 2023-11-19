// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamagebleInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UDamagebleInterface : public UInterface
{
	GENERATED_BODY()
};


class IDamagebleInterface 
{
	GENERATED_BODY()

public: 

	virtual void ApplyDamage(float dmg, ACharacter* Instigator);
	
};
