// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/Styles/StylizedButton.h"

#define LOCTEXT_NAMESPACE "UMG"

UStylizedButton::UStylizedButton()
{
	///Script/SlateCore.SlateWidgetStyleAsset'/Game/UI/Common/Styles/WS_Buttons.WS_Buttons'
	static ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> CustomStyle(TEXT("/Game/UI/Common/Styles/WS_Buttons"));

	SButton::FArguments ButtonDefaults;
	if (CustomStyle.Object)
	{
		ButtonDefaults.ButtonStyle(CustomStyle.Object);
		WidgetStyle = *ButtonDefaults._ButtonStyle;
	}
}

#if WITH_EDITOR
const FText UStylizedButton::GetPaletteCategory()
{
	return LOCTEXT("", "Custom Stylized Button");
}
#endif

#undef LOCTEXT_NAMESPACE