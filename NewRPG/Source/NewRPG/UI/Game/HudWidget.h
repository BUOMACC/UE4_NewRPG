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
	virtual void NativeConstruct() override;

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

	// Dungeon Menu
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDungeonMenu> DungeonMenuClass;

	UPROPERTY()
	class UDungeonMenu* DungeonMenu;

	// Shop
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UShop> ShopClass;

	UPROPERTY()
	class UShop* ShopWidget;

private:
	TArray<class USlot*> QuickSlots;
	int32 MaxZOrder;

public:
	// Show = Visibility
	// Open = AddToViewport
	void ShowInventory(bool Flag);
	void ShowEquipSlot(bool Flag);
	void ShowInteractMark(bool Flag);
	void OpenDungeonMenu();
	void OpenShop(class UDataTable* ShopTable);
};
