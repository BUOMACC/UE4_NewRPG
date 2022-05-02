// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipSlot.generated.h"

class USlot;
class UItem;

/**
 * 
 */
UCLASS()
class NEWRPG_API UEquipSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// 슬롯이 "장착" 옵션을 선택했을 경우의 이벤트를 바인딩하는 함수
	void RegisterEquipEvent();

public:
	UPROPERTY(meta = (BindWidget))
	class UDraggableWindow* WindowTab;

protected:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SlotBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Health;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Atk;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Def;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Crit;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ASpd;

	UPROPERTY()
	TArray<class USlot*> Slots;

public:
	UFUNCTION(BlueprintCallable)
	void SaveEquipSlot();

	UFUNCTION(BlueprintCallable)
	void LoadEquipSlot();

	UFUNCTION(BlueprintPure)
	USlot* GetEmptySlot();

protected:
	UFUNCTION()
	void EquipItem(USlot* TargetSlot);

	UFUNCTION()
	void UnEquipItem(USlot* TargetSlot);

	UFUNCTION()
	void UpdateStatText();

	UFUNCTION()
	void OnStatChanged();

	UFUNCTION()
	void OnClick_CloseButton();
};
