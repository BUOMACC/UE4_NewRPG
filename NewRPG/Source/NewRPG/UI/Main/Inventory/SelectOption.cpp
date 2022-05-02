// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectOption.h"
#include "Components/Button.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Item.h"
#include "Slot.h"


void USelectOption::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Destroy->OnClicked.AddDynamic(this, &USelectOption::OnClick_DestroyButton);
	Btn_Equip->OnClicked.AddDynamic(this, &USelectOption::OnClick_EquipButton);
}


void USelectOption::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	RemoveFromParent();
}


void USelectOption::SetTargetSlot(USlot* Target)
{
	TargetSlot = Target;
	if (Target != nullptr)
	{
		UItem* TargetItem = Target->GetSlotItem();
		if (TargetItem == nullptr)
			return;

		// 장비 아이템인 경우 장착버튼을 보여줌
		if (TargetItem->ItemType == EItemType::Equipment)
		{
			Btn_Equip->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Btn_Equip->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


void USelectOption::OnClick_EquipButton()
{
	if (TargetSlot == nullptr) return;

	if (TargetSlot->OnEquipItem.IsBound())
	{
		TargetSlot->OnEquipItem.Execute(TargetSlot);
	}
	RemoveFromParent();
}


void USelectOption::OnClick_DestroyButton()
{
	if (TargetSlot == nullptr) return;

	TargetSlot->ClearSlot();
	RemoveFromParent();
}