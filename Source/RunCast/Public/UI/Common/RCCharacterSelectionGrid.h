// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Common/RCCharacterGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "Data/RCCharacterSlotData.h"
#include "RCCharacterSelectionGrid.generated.h"

/**
 * 
 */
UCLASS()
class RUNCAST_API URCCharacterSelectionGrid : public UUserWidget
{
	GENERATED_BODY()
	
public: 

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitGrid(URCCharacterSlotData* slotsData);

	UFUNCTION(BlueprintCallable)
	FSlotData GetSelectedSlotData() const;

	UFUNCTION()
	FSlotData GetRandomSlotData() const;

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	TSubclassOf<URCCharacterGridSlot> SlotWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* SlotGridPanel;

	UPROPERTY(BlueprintReadOnly)
	URCCharacterSlotData* CharactersDataObj;

	UPROPERTY(BlueprintReadOnly)
	FSlotData SelectedSlotData;

	UPROPERTY(BlueprintReadOnly)
	URCCharacterGridSlot* SelectedSlotWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotsPerRow;

	UFUNCTION(BlueprintCallable)
	void SetSelectedSlotWidget(URCCharacterGridSlot* slotWidget);

private: 

	

	UFUNCTION()
	int32 GetRow(int32 index);

	UFUNCTION()
	int32 GetColumn(int32 index);
};
