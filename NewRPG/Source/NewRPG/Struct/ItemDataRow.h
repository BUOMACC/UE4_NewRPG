// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemStat.h"
#include "PotionEffect.h"
#include "Engine/DataTable.h"
#include "ItemDataRow.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment,
	Potion,
	Default,
};


USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Item Setting")
	FText DisplayName;

	UPROPERTY(EditAnywhere, Category = "Item Setting", meta = (MultiLine = "true"))
	FText ItemDesc;

	UPROPERTY(EditAnywhere, Category = "Item Setting")
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, Category = "Item Setting")
	int32 MaxCount;

	UPROPERTY(EditAnywhere, Category = "Item Setting")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Setting")
	FItemStat ItemStat;

	UPROPERTY(EditAnywhere, Category = "Item Setting")
	FPotionEffect PotionEffect;
};
