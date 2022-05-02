// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class USlot;
class UItem;

/**
 * Inventory�� GameData�� �����Ǿ� ���˴ϴ�.
 *  - ������ �̵��� �����͸� �����ϱ� ����
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
	// �������� �κ��丮�� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void AddInventory(UItem* NewItem, int32 Count);

	// �κ��丮�� ��� ������ �ʱ�ȭ��Ű�� �Լ� (���־��� ��� - �������� �����ʹ� GameInstance�� ���Ե�)
	UFUNCTION(BlueprintCallable)
	void ClearAllInventory();

	// ����ִ� ������ ��ȯ�ϴ� �Լ�
	UFUNCTION(BlueprintPure)
	USlot* GetEmptySlot();

	// ��밡���� ������ ��ȯ�ϴ� �Լ�
	// - ����ְų� ���� �������� ���� ������ ��ȯ
	UFUNCTION(BlueprintPure)
	USlot* GetAvailableSlot(UItem* ConditionItem, int32 ConditionCount);

	UFUNCTION(BlueprintPure)
	TArray<USlot*> GetAllSlots() { return Slots; }

	// GameData�� �κ��丮 ������ �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void SaveInventory();

	// GameData�� �κ��丮 ������ ������ ���־������� ǥ�����ִ� �Լ�
	UFUNCTION(BlueprintCallable)
	void LoadInventory();

private:
	UFUNCTION()
	void OnClick_CloseButton();

	UFUNCTION()
	FText UpdateGoldText();

	// TOOD: ���� �Ʒ��ΰ��� ����ϴ�.
	UFUNCTION()
	void GiveItem();

	UPROPERTY(EditAnywhere)
	class UDropData* DropData;
};
