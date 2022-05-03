// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlot.h"
#include "Components/HorizontalBox.h"
#include "Entity/Entity.h"
#include "Entity/StatComponent.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Item.h"


void UQuickSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// �����Ե��� ��� SlotBox�κ��� ������
	for (int i = 0; i < SlotBox->GetChildrenCount(); i++)
	{
		USlot* TempSlot = Cast<USlot>(SlotBox->GetChildAt(i));
		if (TempSlot)
		{
			Slots.Add(TempSlot);
		}
	}

	LoadQuickSlot();
}


void UQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

}


void UQuickSlot::NativeDestruct()
{
	Super::NativeDestruct();

	SaveQuickSlot();
}


void UQuickSlot::UseQuickSlot(int32 SlotIndex)
{
	if (Slots.Num() <= SlotIndex) return;

	USlot* TargetSlot = Slots[SlotIndex];
	UItem* TargetItem = TargetSlot->GetSlotItem();

	if (TargetItem != nullptr)
	{
		TargetSlot->AddCount(-1);

		// ȿ�� ����
		AEntity* Target = Cast<AEntity>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Target)
		{
			UStatComponent* StatComp = Target->GetStatComponent();

			// ȸ���� ���
			float TotalHeal_HP = TargetItem->PotionEffect.HealHP + StatComp->GetHealth() * (TargetItem->PotionEffect.HealHP_Ratio / 100.f);
			float TotalHeal_MP = TargetItem->PotionEffect.HealMP + StatComp->GetMana() * (TargetItem->PotionEffect.HealMP_Ratio / 100.f);
			float TotalStamina = TargetItem->PotionEffect.HealStamina;

			StatComp->AddHealth(TotalHeal_HP);
			StatComp->AddMana(TotalHeal_MP);
			StatComp->AddStamina(TotalStamina);
		}
	}
}


void UQuickSlot::SaveQuickSlot()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		Data->QuickSlot[i] = Slots[i]->GetSlotItem();
		Data->QuickSlot_Cnt[i] = Slots[i]->GetItemCount();
	}
}


void UQuickSlot::LoadQuickSlot()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	for (int i = 0; i < Slots.Num(); i++)
	{
		UItem* LoadItem = Data->QuickSlot[i];
		int32 LoadCount = Data->QuickSlot_Cnt[i];
		Slots[i]->SetSlot(LoadItem, LoadCount);
	}
}