// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct/ItemStat.h"
#include "GameData.generated.h"

class UItem;
class UDropData;

/**
 * 
 */
UCLASS()
class NEWRPG_API UGameData : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGameData();

public:
	// * Item ����
	// Ư�� �̸��� �ش��ϴ� �������� �������� �Լ�
	UFUNCTION(BlueprintCallable)
	UItem* GetItemByName(FName ItemName);

	// ������ �������� �������� �Լ�
	UFUNCTION(BlueprintCallable)
	UItem* GetRandomItem();

protected:
	UPROPERTY()
	class UDataTable* ItemTable;

public:
	// Player Slot Data
	UPROPERTY()
	TArray<UItem*> Inventory;

	UPROPERTY()
	TArray<int32> Inventory_Cnt;

	UPROPERTY()
	TArray<UItem*> QuickSlot;

	UPROPERTY()
	TArray<int32> QuickSlot_Cnt;

	UPROPERTY()
	TArray<UItem*> EquipSlot;

	// Player Stat Data
	FItemStat StatData;

	// Player Gold
	int32 Gold;
};
