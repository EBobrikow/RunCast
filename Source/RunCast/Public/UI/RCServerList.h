// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Tools/Globals.h"
#include "RCServerList.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCServerList : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void AddListItem(FServerInfo& data);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* ListView;
	
};
