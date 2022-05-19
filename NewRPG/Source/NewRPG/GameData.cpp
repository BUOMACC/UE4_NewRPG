// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData.h"
#include "Data/DropData.h"
#include "Struct/ItemDataRow.h"
#include "UI/Item.h"


UGameData::UGameData()
{
	// * �⺻ Item Data Table ����
	static ConstructorHelpers::FObjectFinder<UDataTable> DefaultItemTable(TEXT("DataTable'/Game/Data/ItemDataTable.ItemDataTable'"));
	if (DefaultItemTable.Succeeded())
	{
		ItemTable = DefaultItemTable.Object;
	}

	// Reset Player Slot Data
	Inventory.SetNum(42);
	Inventory_Cnt.SetNum(42);

	QuickSlot.SetNum(4);
	QuickSlot_Cnt.SetNum(4);

	EquipSlot.SetNum(5);

	// Reset Player Gold
	Gold = 0;

	// Reset Character Index
	CharacterIndex = 0;
}


UItem* UGameData::GetItemByName(FName ItemName)
{
	FItemDataRow* ItemRow = ItemTable->FindRow<FItemDataRow>(ItemName, TEXT(""));
	if (ItemRow == nullptr)
		return nullptr;

	// * ������ �ν��Ͻ� ����
	UItem* NewItem = NewObject<UItem>(this, UItem::StaticClass());
	NewItem->ItemName = ItemName;
	NewItem->DisplayName = ItemRow->DisplayName;
	NewItem->ItemDesc = ItemRow->ItemDesc;
	NewItem->ItemImage = ItemRow->ItemImage;
	NewItem->MaxCount = ItemRow->MaxCount;
	NewItem->ItemType = ItemRow->ItemType;
	NewItem->ItemStat = ItemRow->ItemStat;
	NewItem->PotionEffect = ItemRow->PotionEffect;

	// * ������ġ - ����(Equipment) Ÿ���� ��������
	//	 ������ MaxCount�� ������ �����ʰ� 1���� �����ϵ��� ����
	if (NewItem->ItemType == EItemType::Equipment)
	{
		NewItem->MaxCount = 1;
	}

	return NewItem;
}


UItem* UGameData::GetRandomItem()
{
	TArray<FName> RowNames = ItemTable->GetRowNames();
	if (RowNames.Num() <= 0)
		return nullptr;

	return GetItemByName(RowNames[FMath::RandRange(0, RowNames.Num() - 1)]);
}


