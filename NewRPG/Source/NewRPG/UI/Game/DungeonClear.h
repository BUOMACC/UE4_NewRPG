// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonClear.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UDungeonClear : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ClearAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FailAnimation;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Ok;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* RewardSlot;

	UPROPERTY()
	TArray<class USlot*> Slots;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

protected:
	UFUNCTION()
	void OnClick_Ok();

public:
	void PlayEndAnimation(bool IsClear) { (IsClear) ? PlayAnimation(ClearAnimation) : PlayAnimation(FailAnimation); }
	void AddRewardsToInventory(class UDropData* NewDropData, int32 Cycle);
	void AddRewardSlot(class UItem* NewItem, int32 Count);
	void AddGoldToInventory(int32 Amount);
};
