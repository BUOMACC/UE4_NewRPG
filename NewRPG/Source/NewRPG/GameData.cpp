// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData.h"
#include "Data/DropData.h"
#include "Struct/ItemDataRow.h"
#include "UI/Item.h"


UGameData::UGameData()
{
	// * 기본 Item Data Table 설정
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

	// * 아이템 인스턴스 생성
	UItem* NewItem = NewObject<UItem>(this, UItem::StaticClass());
	NewItem->ItemName = ItemName;
	NewItem->DisplayName = ItemRow->DisplayName;
	NewItem->ItemDesc = ItemRow->ItemDesc;
	NewItem->ItemImage = ItemRow->ItemImage;
	NewItem->MaxCount = ItemRow->MaxCount;
	NewItem->ItemType = ItemRow->ItemType;
	NewItem->ItemStat = ItemRow->ItemStat;
	NewItem->PotionEffect = ItemRow->PotionEffect;

	// * 안전장치 - 장착(Equipment) 타입의 아이템은
	//	 설정된 MaxCount의 영향을 받지않고 1개만 보유하도록 고정
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


