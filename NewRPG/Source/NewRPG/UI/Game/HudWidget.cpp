// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Data/BuffData.h"
#include "Entity/BuffComponent.h"
#include "UI/Main/DraggableWindow.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/EquipSlot.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Game/BuffIcon.h"


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


void UHudWidget::AddBuffIcon(UBuffData* Buff)
{
	if (BuffIconClass == nullptr) return;

	for (int i = 0; i < BuffList->GetChildrenCount(); i++)
	{
		UBuffIcon* TempIcon = Cast<UBuffIcon>(BuffList->GetChildAt(i));
		if (TempIcon && TempIcon->GetBuffData() == Buff)
		{
			// 중복된 버프라면 지속시간만 갱신
			TempIcon->SetBuffIconDuration(Buff->Duration);
			return;
		}
	}

	// 중복된 버프가 아니면 아이콘 추가
	UBuffIcon* BuffIcon = CreateWidget<UBuffIcon>(this, BuffIconClass);
	BuffIcon->SetBuffData(Buff);
	BuffList->AddChild(BuffIcon);
}


void UHudWidget::RemoveBuffIcon(UBuffData* Buff)
{
	if (BuffList->GetChildrenCount() == 0) return;

	for (int i = 0; i < BuffList->GetChildrenCount(); i++)
	{
		UBuffIcon* TempIcon = Cast<UBuffIcon>(BuffList->GetChildAt(i));
		if (TempIcon && TempIcon->GetBuffData() == Buff)
		{
			// 만료된 버프를 목록에서 삭제
			BuffList->RemoveChildAt(i);
			return;
		}
	}
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