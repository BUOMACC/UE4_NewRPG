// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonClear.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Controller/PlayerGameController.h"
#include "Data/DropData.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Item.h"


void UDungeonClear::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Ok->OnClicked.AddDynamic(this, &UDungeonClear::OnClick_Ok);

	for (int i = 0; i < RewardSlot->GetChildrenCount(); i++)
	{
		USlot* TmpSlot = Cast<USlot>(RewardSlot->GetChildAt(i));
		if (TmpSlot)
		{
			Slots.Add(TmpSlot);
		}
	}
}


void UDungeonClear::OnClick_Ok()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenLoadingScreen(TEXT("Village"), 3.0f);
	}
}


void UDungeonClear::AddRewardsToInventory(UDropData* NewDropData, int32 Cycle)
{
	if (NewDropData == nullptr || Slots.Num() == 0) return;
	if (NewDropData->Drops.Num() == 0) return;

	// Cycle번 반복하여 Reward 아이템을 인벤토리에 추가
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		UInventory* Inventory = PC->GetInventory();
		for (int i = 0; i < Cycle; i++)
		{
			int32 RandNum = FMath::RandRange(0, NewDropData->Drops.Num() - 1);
			int32 Count = FMath::RandRange(NewDropData->Drops[RandNum].Min_Count, NewDropData->Drops[RandNum].Max_Count);
			UItem* NewItem = Data->GetItemByName(NewDropData->Drops[RandNum].ItemName);

			// 해당하는 아이템이 있는 경우에만 추가
			if (NewItem)
			{
				Inventory->AddInventory(NewItem, Count);
				AddRewardSlot(NewItem, Count);
			}
		}
	}
}


void UDungeonClear::AddRewardSlot(UItem* NewItem, int32 Count)
{
	for (USlot* CurSlot : Slots)
	{
		if (CurSlot->IsEmptySlot())
		{
			CurSlot->SetSlot(NewItem, Count);
			return;
		}
	}
}


void UDungeonClear::AddGoldToInventory(int32 Amount)
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	FTextFormat Format = FTextFormat(FText::FromString(TEXT("{0}")));
	Text_Gold->SetText(FText::Format(Format, Amount));
	Data->Gold += Amount;
}