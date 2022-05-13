// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "Controller/PlayerGameController.h"
#include "Data/DropData.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Main/Inventory/Slot.h"


void UDungeonMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectStage = 0;

	Btn_Close->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_CloseButton);
	Btn_Stage1->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_Stage1);
	Btn_Start->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_Start);

	// 슬롯 저장
	for (int i = 0; i < RewardSlot->GetChildrenCount(); i++)
	{
		USlot* TempSlot = Cast<USlot>(RewardSlot->GetChildAt(i));
		if (TempSlot)
		{
			Slots.Add(TempSlot);
		}
	}

	// 기대보상 설정
	SetRewardSlot(DropData[SelectStage]);
}


void UDungeonMenu::OnClick_CloseButton()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	RemoveFromParent();
}


void UDungeonMenu::OnClick_Stage1()
{
	ImageSwitcher->SetActiveWidgetIndex(0);
	SelectStage = 0;
}


void UDungeonMenu::OnClick_Start()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC == nullptr) return;

	PC->AddUIStack(-1);
	switch (SelectStage)
	{
	case 0:
		PC->OpenLoadingScreen(TEXT("StageGideon"), 3.0f);
		break;
	}
}


void UDungeonMenu::SetRewardSlot(UDropData* NewDropData)
{
	if (NewDropData && Slots.Num() != 0)
	{
		int32 SlotIndex = 0;
		UGameData* Data = Cast<UGameData>(GetGameInstance());
		for (int i = 0; i < NewDropData->Drops.Num(); i++)
		{
			UItem* Item = Data->GetItemByName(NewDropData->Drops[i].ItemName);
			if (Item)
			{
				Slots[SlotIndex]->SetSlot(Item, 1);
				Slots[SlotIndex]->HideItemCount(true);
				SlotIndex++;
			}
		}
	}
}