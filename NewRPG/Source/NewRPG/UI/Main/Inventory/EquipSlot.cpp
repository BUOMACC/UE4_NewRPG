// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSlot.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Item.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Main/DraggableWindow.h"
#include "GameData.h"


void UEquipSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WindowTab->Btn_Close->OnClicked.AddDynamic(this, &UEquipSlot::OnClick_CloseButton);
}


void UEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	WindowTab->SetDraggableWindow(FText::FromString(TEXT("Equipment")), this);

	// 퀵슬롯들을 모두 SlotBox로부터 가져옴
	for (int i = 0; i < SlotBox->GetChildrenCount(); i++)
	{
		USlot* TempSlot = Cast<USlot>(SlotBox->GetChildAt(i));
		if (TempSlot)
		{
			TempSlot->OnUnEquipItem.BindUFunction(this, TEXT("UnEquipItem"));
			Slots.Add(TempSlot);
		}
	}

	RegisterEquipEvent();
	LoadEquipSlot();
}


void UEquipSlot::NativeDestruct()
{
	Super::NativeDestruct();

	SaveEquipSlot();
}


void UEquipSlot::OnClick_CloseButton()
{
	SetVisibility(ESlateVisibility::Hidden);

	// PlayerController에서 UI Stack을 1감소시킴
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	SaveEquipSlot();
}


void UEquipSlot::SaveEquipSlot()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		Data->EquipSlot[i] = Slots[i]->GetSlotItem();
	}
}


void UEquipSlot::LoadEquipSlot()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		UItem* LoadItem = Data->EquipSlot[i];
		Slots[i]->SetSlot(LoadItem, 1);
	}

	UpdateStatText();
}


USlot* UEquipSlot::GetEmptySlot()
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i]->GetSlotItem() == nullptr)
		{
			return Slots[i];
		}
	}
	return nullptr;
}


void UEquipSlot::RegisterEquipEvent()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		TArray<USlot*> InvSlots = PC->GetInventory()->GetAllSlots();
		if (InvSlots.Num() <= 0) return;

		for (int i = 0; i < InvSlots.Num(); i++)
		{
			// * Inventory Slot이 "장착" 옵션을 선택했을때 아이템 착용 이벤트가 발생되도록 등록
			InvSlots[i]->OnEquipItem.BindUFunction(this, TEXT("EquipItem"));
		}
	}
}


void UEquipSlot::EquipItem(USlot* TargetSlot)
{
	if (TargetSlot == nullptr) return;

	USlot* EmptySlot = GetEmptySlot();
	UItem* TargetItem = TargetSlot->GetSlotItem();

	if (EmptySlot && TargetItem->ItemType == EItemType::Equipment)
	{
		EmptySlot->SetSlot(TargetItem, 1);
		TargetSlot->ClearSlot();
		UpdateStatText();
		OnStatChanged();
	}
}


void UEquipSlot::UnEquipItem(USlot* TargetSlot)
{
	if (TargetSlot == nullptr || TargetSlot->GetSlotItem() == nullptr) return;

	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		USlot* EmptySlot = PC->GetInventory()->GetEmptySlot();
		UItem* TargetItem = TargetSlot->GetSlotItem();

		// 인벤토리가 가득찼으면 작업을 중지
		if (EmptySlot == nullptr) return;

		EmptySlot->SetSlot(TargetItem, 1);
		TargetSlot->ClearSlot();
		UpdateStatText();
		OnStatChanged();
	}
}


void UEquipSlot::UpdateStatText()
{
	FItemStat StatData;
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i]->GetSlotItem() != nullptr)
		{
			StatData += Slots[i]->GetSlotItem()->ItemStat;
		}
	}

	StatData.Defence = FMath::Clamp(StatData.Defence, 0.f, 100.f);
	StatData.CritChance = FMath::Clamp(StatData.Defence, 0.f, 100.f);
	StatData.AttackSpd = FMath::Clamp(StatData.AttackSpd, 0.f, 40.f);

	// Text 갱신
	Text_Health->SetText(FText::AsNumber(StatData.Health));
	Text_Atk->SetText(FText::AsNumber(StatData.Strength));
	Text_Def->SetText(FText::AsNumber(StatData.Defence));
	Text_Crit->SetText(FText::AsNumber(StatData.CritChance));
	Text_ASpd->SetText(FText::AsNumber(StatData.AttackSpd));

	// GameData에 스텟 정보를 저장해둠
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	if (Data)
	{
		Data->StatData = StatData;
	}
}


void UEquipSlot::OnStatChanged()
{
	// 스텟을 캐릭터에 반영
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ApplyStat();
	}
}