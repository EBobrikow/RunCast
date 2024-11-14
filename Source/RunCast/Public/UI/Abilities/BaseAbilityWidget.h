// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "BaseAbilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API UBaseAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag RelatedCooldownTag;

	UFUNCTION()
	void OnTagCooldownRecieved(FGameplayTag Tag, float renmaining, float duration);

	virtual void RelatedCooldownTagRecieved(float renmaining, float duration);
	
};
