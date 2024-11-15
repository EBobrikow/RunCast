// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/RCDamageDirectionWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

void URCDamageDirectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayer())
	{
		CashedCharacter = Cast<ACharacter>(GetOwningPlayer()->GetPawn());
	}

	
	
}

void URCDamageDirectionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CashedCharacter && DamageSource)
	{
		FVector characterLocation = CashedCharacter->GetActorLocation();
		FVector sourceLocation = DamageSource->GetActorLocation();
		FRotator look = UKismetMathLibrary::FindLookAtRotation(characterLocation, sourceLocation);
		FRotator controlRot = CashedCharacter->GetControlRotation();
		float renderAngle = look.Yaw - controlRot.Yaw;
		if (DirectionImage)
		{
			DirectionImage->SetRenderTransformAngle(renderAngle);
		}
	}
}

void URCDamageDirectionWidget::InitAnimation()
{
	if (ImageFade)
	{
		FWidgetAnimationDynamicEvent finishDlegate;
		finishDlegate.BindDynamic(this, &URCDamageDirectionWidget::AnimationFinished);
		BindToAnimationFinished(ImageFade, finishDlegate);
		PlayAnimation(ImageFade);
	}
}

void URCDamageDirectionWidget::AnimationFinished()
{
	RemoveFromParent();
	
}
