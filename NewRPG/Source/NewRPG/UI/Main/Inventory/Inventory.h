// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class USlot;
class UItem;

/**
 * Inventory는 GameData와 연동되어 사용됩니다.
 *  - 레벨간 이동시 데이터를 저장하기 위함
 */
UCLASS()
class NEWRPG_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UDraggableWindow* WindowTab;

protected:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox_Slots;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ItemGiver;

	UPROPERTY()
	TArray<class USlot*> Slots;

public:
	// 아이템을 인벤토리에 지급하는 함수
	UFUNCTION(BlueprintCallable)
	void AddInventory(UItem* NewItem, int32 Count);

	// 인벤토리의 모든 슬롯을 초기화시키는 함수 (비주얼적 요소 - 실질적인 데이터는 GameInstance에 포함됨)
	UFUNCTION(BlueprintCallable)
	void ClearAllInventory();

	// 비어있는 슬롯을 반환하는 함수
	UFUNCTION(BlueprintPure)
	USlot* GetEmptySlot();

	// 사용가능한 슬롯을 반환하는 함수
	// - 비어있거나 같은 아이템을 가진 슬롯을 반환
	UFUNCTION(BlueprintPure)
	USlot* GetAvailableSlot(UItem* ConditionItem, int32 ConditionCount);

	UFUNCTION(BlueprintPure)
	TArray<USlot*> GetAllSlots() { return Slots; }

	// GameData에 인벤토리 정보를 저장하는 함수
	UFUNCTION(BlueprintCallable)
	void SaveInventory();

	// GameData에 인벤토리 정보를 가져와 비주얼적으로 표시해주는 함수
	UFUNCTION(BlueprintCallable)
	void LoadInventory();

private:
	UFUNCTION()
	void OnClick_CloseButton();

	UFUNCTION()
	FText UpdateGoldText();

	// TOOD: 이후 아래두개는 지웁니다.
	UFUNCTION()
	void GiveItem();

	UPROPERTY(EditAnywhere)
	class UDropData* DropData;
};
