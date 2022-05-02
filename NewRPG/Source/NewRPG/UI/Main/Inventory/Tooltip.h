// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tooltip.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UTooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetTooltipItem(UItem* TargetItem);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Desc;

	// *** Stat Text ***
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Health;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Strength;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Defence;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CritChance;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_AttackSpeed;

	// *** Potion Text ***
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_HealHP;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_HealMP;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_HealStamina;
};
