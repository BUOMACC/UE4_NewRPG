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
#include "UI/Main/Shop.h"
#include "UI/Game/DungeonMenu.h"


void UHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Inventory->WindowTab->OnDragWindowClick.BindUFunction(this, TEXT("BringToFront"));
	EquipSlot->WindowTab->OnDragWindowClick.BindUFunction(this, TEXT("BringToFront"));
}


void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// * Create DungeonMenu
	if (DungeonMenuClass)
	{
		DungeonMenu = CreateWidget<UDungeonMenu>(this, DungeonMenuClass);
	}

	// * Create Shop
	if (ShopClass)
	{
		ShopWidget = CreateWidget<UShop>(this, ShopClass);
	}
}


void UHudWidget::BringToFront(UUserWidget* TargetWidget)
{
	MaxZOrder = MaxZOrder + 1;
	if (MaxZOrder >= 10000000)
		MaxZOrder -= 10000000;
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


void UHudWidget::OpenDungeonMenu()
{
	if (DungeonMenu == nullptr && DungeonMenu->IsInViewport()) return;

	FVector2D Pos = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	DungeonMenu->SetDesiredSizeInViewport(FVector2D(1200, 700));
	DungeonMenu->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	DungeonMenu->SetPositionInViewport(Pos / 2, true);
	DungeonMenu->AddToViewport();
}


void UHudWidget::OpenShop(UDataTable* ShopTable)
{
	if (ShopTable == nullptr || ShopWidget == nullptr || ShopWidget->IsInViewport()) return;

	FVector2D Pos = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	ShopWidget->SetDesiredSizeInViewport(FVector2D(800, 600));
	ShopWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	ShopWidget->SetPositionInViewport(Pos / 2, true);
	ShopWidget->ShopTable = ShopTable;
	ShopWidget->AddToViewport();
}