// Fill out your copyright notice in the Description page of Project Settings.


#include "Tooltip.h"
#include "Components/TextBlock.h"
#include "UI/Item.h"


void UTooltip::SetTooltipItem(UItem* TargetItem)
{
	Text_Title->SetText(TargetItem->DisplayName);
	Text_Desc->SetText(TargetItem->ItemDesc);

	FTextFormat Format;
	FItemStat& ItemStat = TargetItem->ItemStat;
	FPotionEffect& PotionEffect = TargetItem->PotionEffect;

	// * ItemStat
	// - Update Health Text
	if (ItemStat.Health > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("+{0} 최대 체력")));
		Text_Health->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_Health->SetText(FText::Format(Format, ItemStat.Health));
	}
	else
	{
		Text_Health->SetVisibility(ESlateVisibility::Collapsed);
	}

	// - Update Strength Text
	if (ItemStat.Strength > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("+{0} 공격력")));
		Text_Strength->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_Strength->SetText(FText::Format(Format, ItemStat.Strength));
	}
	else
	{
		Text_Strength->SetVisibility(ESlateVisibility::Collapsed);
	}

	// - Update Defence Text
	if (ItemStat.Defence > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("+{0}% 방어력")));
		Text_Defence->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_Defence->SetText(FText::Format(Format, ItemStat.Defence));
	}
	else
	{
		Text_Defence->SetVisibility(ESlateVisibility::Collapsed);
	}

	// - Update CritChance Text
	if (ItemStat.CritChance > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("+{0}% 크리티컬 확률")));
		Text_CritChance->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_CritChance->SetText(FText::Format(Format, ItemStat.CritChance));
	}
	else
	{
		Text_CritChance->SetVisibility(ESlateVisibility::Collapsed);
	}

	// - Update AttackSpeed Text
	if (ItemStat.AttackSpd > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("+{0}% 공격속도")));
		Text_AttackSpeed->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_AttackSpeed->SetText(FText::Format(Format, ItemStat.AttackSpd));
	}
	else
	{
		Text_AttackSpeed->SetVisibility(ESlateVisibility::Collapsed);
	}

	// * PotionEffect
	// - Update Heal HP Text
	if (PotionEffect.HealHP <= 0 && PotionEffect.HealHP_Ratio <= 0)
		Text_HealHP->SetVisibility(ESlateVisibility::Collapsed);

	if (PotionEffect.HealHP > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("{0}의 체력을 회복")));
		Text_HealHP->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_HealHP->SetText(FText::Format(Format, PotionEffect.HealHP));
	}

	// - Update Heal HP Text (Ratio)
	if (PotionEffect.HealHP_Ratio > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("최대 체력의 {0}% 체력을 회복")));
		Text_HealHP->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_HealHP->SetText(FText::Format(Format, PotionEffect.HealHP_Ratio));
	}

	// - Update Heal MP Text
	if (PotionEffect.HealMP <= 0 && PotionEffect.HealMP_Ratio <= 0)
		Text_HealMP->SetVisibility(ESlateVisibility::Collapsed);

	if (PotionEffect.HealMP > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("{0}의 마나를 회복")));
		Text_HealMP->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_HealMP->SetText(FText::Format(Format, PotionEffect.HealMP));
	}

	// - Update Heal MP Text (Ratio)
	if (PotionEffect.HealMP_Ratio > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("{0}% 마나를 회복")));
		Text_HealMP->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_HealMP->SetText(FText::Format(Format, PotionEffect.HealMP_Ratio));
	}

	// - Update Heal Stamina Text
	if (PotionEffect.HealStamina > 0)
	{
		Format = FTextFormat(FText::FromString(TEXT("{0}의 스테미너를 회복")));
		Text_HealStamina->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text_HealStamina->SetText(FText::Format(Format, PotionEffect.HealStamina));
	}
	else
	{
		Text_HealStamina->SetVisibility(ESlateVisibility::Collapsed);
	}
}