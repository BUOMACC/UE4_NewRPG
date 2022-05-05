// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectButton.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "MenuGameMode.h"


void UCharacterSelectButton::NativeConstruct()
{
	Super::NativeConstruct();

	// Setting Portrait
	Image_Portrait->SetBrushFromTexture(CharacterIcon, false);

	// Set Outline Color
	Outline->SetBrushColor(OriginColor);
}


void UCharacterSelectButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	Outline->SetBrushColor(HighlightColor);
}


void UCharacterSelectButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Outline->SetBrushColor(OriginColor);
}


FReply UCharacterSelectButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	// Button Click Event
	AMenuGameMode* GM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	return Reply.Handled();
}