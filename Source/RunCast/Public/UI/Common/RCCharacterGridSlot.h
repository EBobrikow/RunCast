// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/RCCharacterSlotData.h"
#include "RCCharacterGridSlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotSelected, URCCharacterGridSlot*, slotWidget);

UCLASS()
class RUNCAST_API URCCharacterGridSlot : public UUserWidget
{
	GENERATED_BODY()

public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitSlot(const FSlotData& slotData);

	UFUNCTION(BlueprintCallable)
	FSlotData GetData() const;

	UPROPERTY()
	FOnSlotSelected OnSlotSelected;

	UFUNCTION(BlueprintCallable)
	void SelectSlot();

	UFUNCTION(BlueprintCallable)
	void DeselectSlot();

protected: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* OverlapImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SelectedImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CharacterIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CharacterNameTxt;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FSlotData CharacterData;

	UFUNCTION()
	bool IsSelected() const;

	UFUNCTION(BlueprintCallable)
	void OnMouseStartOverlap();

	UFUNCTION(BlueprintCallable)
	void OnMouseEndOverlap();

	UFUNCTION(BlueprintCallable)
	void OnSlotClicked();

	

};
