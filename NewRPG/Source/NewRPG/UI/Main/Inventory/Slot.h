// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slot.generated.h"

class UItem;
class UDragVisual;
class UTooltip;
class USelectOption;

/**
 * 
 */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	Equipment,
	QuickSlot,
	OnlySee,
	Inventory,
};

// SelectOption���� ������ �����ɼ��� ���������� �̺�Ʈ
DECLARE_DELEGATE_OneParam(FOnEquipItem, USlot*);
DECLARE_DELEGATE_OneParam(FOnUnEquipItem, USlot*);

UCLASS()
class NEWRPG_API USlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// *** Delegate ***
	FOnEquipItem OnEquipItem;
	FOnUnEquipItem OnUnEquipItem;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply OnLeftMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	FReply OnRightMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// �Ʒ� 4���� �������̵� �Լ��� ���Կ� ���콺�� ������ ������� ȿ���� ���� ���
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	// ���Կ� �������� �����ϴ� ���
	UFUNCTION(BlueprintCallable)
	void SetSlot(UItem* NewItem, int32 NewCount);

	// ���Կ� �������� �ִ°��, �ش� �������� ī��Ʈ�� ����
	UFUNCTION(BlueprintCallable)
	void SetCount(int32 NewCount);

	// ���Կ� �������� �ִ°��, �ش� �������� ī��Ʈ�� ����/����
	UFUNCTION(BlueprintCallable)
	void AddCount(int32 Amount);

	// ������ �ʱ�ȭ��Ű�� ���
	UFUNCTION(BlueprintCallable)
	void ClearSlot();

	// ������ �������� ���� ��ȯ�ϴ� ���
	UFUNCTION(BlueprintCallable)
	void SwapSlot(USlot* NewSlot);

	// ������ ������ī��Ʈ�� ����� ���
	UFUNCTION(BlueprintCallable)
	void HideItemCount(bool Flag);

	// ������ ����ִ���
	UFUNCTION(BlueprintPure)
	bool IsEmptySlot();

	// ������ ���� �������� ��ȯ
	UFUNCTION(BlueprintPure)
	UItem* GetSlotItem();

	// ������ ���� ������ ������ ��ȯ
	UFUNCTION(BlueprintPure)
	int32 GetItemCount();

protected:
	UItem* Item;
	int32 Count;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Outline;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Count;

	UPROPERTY(EditAnywhere)
	ESlotType SlotType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDragVisual> DragVisualClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTooltip> TooltipClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USelectOption> SelectOptionClass;

	// ���Կ� ���콺�� �����ٴ��� �� �׵θ� ���� ����ȿ��
	UPROPERTY(EditAnywhere)
	FLinearColor OriginColor;

	UPROPERTY(EditAnywhere)
	FLinearColor HighlightColor;

private:
	UPROPERTY()
	class UTooltip* TooltipWidgetRef;

	UPROPERTY()
	class USelectOption* SelectOptionRef;

	UFUNCTION()
	UWidget* TooltipUpdate();
};
