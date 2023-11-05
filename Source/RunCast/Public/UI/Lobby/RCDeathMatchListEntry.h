// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "RCDeathMatchListEntry.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNCAST_API URCDeathMatchListEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerAuthorityImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ReadyImg;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* GameMasterIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ConnectedPlayerIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* AiBotIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* PlayerReadyIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* PlayerIdleIcon;

	UFUNCTION(BlueprintCallable)
	void SetTextureToImage(UImage* Img, UTexture2D* texture);
	
};
