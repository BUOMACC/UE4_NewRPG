// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Slot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Controller/PlayerGameController.h"
#include "Data/DropData.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "Struct/DropInfo.h"
#include "UI/Item.h"
#include "UI/Main/DraggableWindow.h"


void UInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WindowTab->Btn_Close->OnClicked.AddDynamic(this, &UInventory::OnClick_CloseButton);
	Text_Gold->TextDelegate.BindUFunction(this, TEXT("UpdateGoldText"));
}


void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	WindowTab->SetDraggableWindow(FText::FromString(TEXT("Inventory")), this);
	Btn_ItemGiver->OnClicked.AddDynamic(this, &UInventory::GiveItem);

	// 인벤토리 슬롯들을 모두 WrapBox_Slots 로부터 가져옴
	for (int i = 0; i < WrapBox_Slots->GetChildrenCount(); i++)
	{
		USlot* TempSlot = Cast<USlot>(WrapBox_Slots->GetChildAt(i));
		if (TempSlot)
		{
			Slots.Add(TempSlot);
		}
	}

	LoadInventory();
}


void UInventory::NativeDestruct()
{
	Super::NativeDestruct();

	SaveInventory();
}


void UInventory::AddInventory(UItem* NewItem, int32 Count)
{
	if (NewItem == nullptr) return;

	USlot* AvailableSlot = GetAvailableSlot(NewItem, Count);
	if (AvailableSlot)
	{
		AvailableSlot->SetSlot(NewItem, AvailableSlot->GetItemCount() + Count);
	}
}


void UInventory::ClearAllInventory()
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		USlot* CurrentSlot = Cast<USlot>(Slots[i]);
		if (CurrentSlot)
		{
			CurrentSlot->ClearSlot();
		}
	}
}


USlot* UInventory::GetEmptySlot()
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		USlot* CurrentSlot = Slots[i];
		if (CurrentSlot && CurrentSlot->IsEmptySlot())
		{
			return CurrentSlot;
		}
	}
	return nullptr;
}


USlot* UInventory::GetAvailableSlot(UItem* ConditionItem, int32 ConditionCount)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		USlot* CurrentSlot = Slots[i];
		// 1) 비어있는 슬롯을 우선반환
		if (CurrentSlot->GetSlotItem() == nullptr)
			return CurrentSlot;

		// 2) 같은 아이템이고, 슬롯에 있는 아이템 개수가 초과되지 않는 슬롯을 반환
		if (CurrentSlot->GetSlotItem()->ItemName == ConditionItem->ItemName
			&& CurrentSlot->GetItemCount() + ConditionCount <= CurrentSlot->GetSlotItem()->MaxCount)
			return CurrentSlot;
	}
	return nullptr;
}


void UInventory::GiveItem()
{
	UGameData* Data = Cast<UGameData>(GetWorld()->GetGameInstance());
	if (Data)
	{
		int32 DataMax = DropData->Drops.Num();
		FDropInfo DropInfo = DropData->Drops[FMath::RandRange(0, DataMax - 1)];
		UItem* NewItem = Data->GetItemByName(DropInfo.ItemName);
		AddInventory(NewItem, FMath::RandRange(DropInfo.Min_Count, DropInfo.Max_Count));

		Data->Gold += FMath::RandRange(0, 10000000);
	}
}


void UInventory::OnClick_CloseButton()
{
	SetVisibility(ESlateVisibility::Hidden);

	// PlayerController에서 UI Stack을 1감소시킴
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	SaveInventory();
}


FText UInventory::UpdateGoldText()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	if (Data)
	{
		FTextFormat Format = FTextFormat(FText::FromString(TEXT("{0}")));
		return FText::Format(Format, Data->Gold);
	}
	return FText::FromString(TEXT("0"));
}


void UInventory::SaveInventory()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		USlot* CurrentSlot = Cast<USlot>(Slots[i]);
		if (CurrentSlot)
		{
			Data->Inventory[i] = CurrentSlot->GetSlotItem();
			Data->Inventory_Cnt[i] = CurrentSlot->GetItemCount();
		}
	}
}


void UInventory::LoadInventory()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		USlot* CurrentSlot = Cast<USlot>(Slots[i]);
		if (CurrentSlot)
		{
			UItem* LoadItem = Data->Inventory[i];
			int32 LoadCount = Data->Inventory_Cnt[i];
			CurrentSlot->SetSlot(LoadItem, LoadCount);
		}
	}
}