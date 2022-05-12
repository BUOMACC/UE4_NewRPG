// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonClear.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"
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


void UDungeonClear::AddReward(UItem* NewItem, int32 Count)
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