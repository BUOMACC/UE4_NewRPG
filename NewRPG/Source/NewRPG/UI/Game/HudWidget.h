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

	// 드래그를 통해 위치변경이 가능한 위젯(Draggable Window)
	// 클릭시 화면의 맨 앞으로 가져오는 함수
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


private:
	UPROPERTY()
	TArray<class USlot*> QuickSlots;
	int32 MaxZOrder;

public:
	// * Show : Collapsed / Visibility를 통한 표시
	void ShowInventory(bool Flag);
	void ShowEquipSlot(bool Flag);
	void ShowInteractMark(bool Flag);
};
