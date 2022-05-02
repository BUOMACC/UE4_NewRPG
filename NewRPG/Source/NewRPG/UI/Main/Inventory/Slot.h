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

// SelectOption에서 아이템 장착옵션을 선택했을때 이벤트
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

	// 아래 4개의 오버라이드 함수는 슬롯에 마우스를 가져다 대었을때 효과를 위해 사용
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	// 슬롯에 아이템을 설정하는 기능
	UFUNCTION(BlueprintCallable)
	void SetSlot(UItem* NewItem, int32 NewCount);

	// 슬롯에 아이템이 있는경우, 해당 아이템의 카운트를 조정
	UFUNCTION(BlueprintCallable)
	void SetCount(int32 NewCount);

	// 슬롯에 아이템이 있는경우, 해당 아이템의 카운트를 증가/감소
	UFUNCTION(BlueprintCallable)
	void AddCount(int32 Amount);

	// 슬롯을 초기화시키는 기능
	UFUNCTION(BlueprintCallable)
	void ClearSlot();

	// 슬롯의 아이템을 서로 교환하는 기능
	UFUNCTION(BlueprintCallable)
	void SwapSlot(USlot* NewSlot);

	// 슬롯의 아이템카운트를 숨기는 기능
	UFUNCTION(BlueprintCallable)
	void HideItemCount(bool Flag);

	// 슬롯이 비어있는지
	UFUNCTION(BlueprintPure)
	bool IsEmptySlot();

	// 슬롯이 가진 아이템을 반환
	UFUNCTION(BlueprintPure)
	UItem* GetSlotItem();

	// 슬롯이 가진 아이템 개수를 반환
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

	// 슬롯에 마우스를 가져다댔을 때 테두리 색상 변경효과
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
