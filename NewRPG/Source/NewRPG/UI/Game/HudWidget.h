// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	// �巡�׸� ���� ��ġ������ ������ ����(Draggable Window)
	// Ŭ���� ȭ���� �� ������ �������� �Լ�
	UFUNCTION()
	void BringToFront(UUserWidget* TargetWidget);

public:
	UPROPERTY(meta = (BindWidget))
	class UStatusWidget* StatusWidget;

	UPROPERTY(meta = (BindWidget))
	class UInventory* Inventory;

	UPROPERTY(meta = (BindWidget))
	class UEquipSlot* EquipSlot;

	UPROPERTY(meta = (BindWidget))
	class UQuickSlot* QuickSlot;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* InteractMark;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* BuffList;

protected:
	// BuffIcon Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuffIcon> BuffIconClass;

private:
	UPROPERTY()
	TArray<class USlot*> QuickSlots;
	int32 MaxZOrder;

public:
	// ������ �޾����� ȣ���ų �Լ�
	void AddBuffIcon(class UBuffData* Buff);
	void RemoveBuffIcon(class UBuffData* Buff);

	// * Show : Collapsed / Visibility�� ���� ǥ��
	void ShowInventory(bool Flag);
	void ShowEquipSlot(bool Flag);
	void ShowInteractMark(bool Flag);
};
