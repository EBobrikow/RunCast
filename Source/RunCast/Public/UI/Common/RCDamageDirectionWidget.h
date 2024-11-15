// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "RCDamageDirectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCDamageDirectionWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	AActor* DamageSource = nullptr;

	UFUNCTION()
	void InitAnimation();

protected: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* DirectionImage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ImageFade;

	UPROPERTY()
	ACharacter* CashedCharacter;

	UFUNCTION()
	void AnimationFinished();
	
};
