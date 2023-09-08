// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Tools/Globals.h"
#include "Components/Button.h"
#include "Core/RCGameInstance.h"
#include "RCServerListViewItem.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCServerListViewItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FServerInfo serverInfoData;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinServerBtn;

protected:

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClicked();

	UPROPERTY()
	URCGameInstance* GameInst;
};
