// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Main/DraggableWindow.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/EquipSlot.h"
#include "UI/Main/Inventory/Slot.h"


void UHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Inventory->WindowTab->OnDragWindowClick.BindUFunction(this, TEXT("BringToFront"));
	EquipSlot->WindowTab->OnDragWindowClick.BindUFunction(this, TEXT("BringToFront"));
}


void UHudWidget::BringToFront(UUserWidget* TargetWidget)
{
	MaxZOrder = (MaxZOrder + 1) % 10000000;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(TargetWidget)->SetZOrder(MaxZOrder);
}


void UHudWidget::ShowInventory(bool Flag)
{
	if (Flag)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UHudWidget::ShowEquipSlot(bool Flag)
{
	if (Flag)
	{
		EquipSlot->SetVisibility(ESlateVisibility::Visible);
		EquipSlot->LoadEquipSlot();
	}
	else
	{
		EquipSlot->SetVisibility(ESlateVisibility::Hidden);
		EquipSlot->SaveEquipSlot();
	}
}


void UHudWidget::ShowInteractMark(bool Flag)
{
	if (Flag)
	{
		InteractMark->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InteractMark->SetVisibility(ESlateVisibility::Hidden);
	}
}