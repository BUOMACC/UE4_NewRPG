// Fill out your copyright notice in the Description page of Project Settings.


#include "Slot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DragVisual.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Item.h"
#include "Tooltip.h"
#include "SelectOption.h"


void USlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Img_Item->ToolTipWidgetDelegate.BindUFunction(this, FName("TooltipUpdate"));
}


void USlot::NativeConstruct()
{
	Super::NativeConstruct();

	// Tooltip Widget ����
	TooltipWidgetRef = CreateWidget<UTooltip>(this, TooltipClass);

	// SelectOption Widget ����
	SelectOptionRef = CreateWidget<USelectOption>(this, SelectOptionClass);

	Img_Item->SynchronizeProperties();
	Outline->SetBrushColor(OriginColor);
}


FReply USlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply ResultReply;
	ResultReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// �������� ���°�� ����
	if (Item == nullptr)
		return ResultReply.NativeReply;

	// Left Button Down
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		ResultReply.NativeReply = OnLeftMouseButtonDown(InGeometry, InMouseEvent);
	}
	// Right Button Down
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		ResultReply.NativeReply = OnRightMouseButtonDown(InGeometry, InMouseEvent);
	}

	return ResultReply.NativeReply;
}


FReply USlot::OnLeftMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply ResultReply;
	ResultReply.NativeReply = FReply::Unhandled();

	// * �̰��� ���콺 ��Ŭ���� ���� ���� �ۼ�

	// - OnlySee Ÿ���� ������ ���⸸ �����ϹǷ� ����
	// - Equipment Ÿ���� ������ �巡�׸� ������� �ʰ� ��Ŭ���� ���
	if (SlotType == ESlotType::OnlySee || SlotType == ESlotType::Equipment)
		return ResultReply.NativeReply;

	// �巡�� ����
	ResultReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	return ResultReply.NativeReply;
}


FReply USlot::OnRightMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply ResultReply;
	ResultReply.NativeReply = FReply::Unhandled();

	// * �̰��� ���콺 ��Ŭ���� ���� ���� �ۼ�
	
	// [Equipment] : RightClick - ��� ��������
	if (SlotType == ESlotType::Equipment && OnUnEquipItem.IsBound())
	{
		OnUnEquipItem.Execute(this);
	}
	
	// [Inventory] : Ctrl + RightClick - �����ۿ� ���� ���ÿɼ� (����, ������..) ǥ��
	if (InMouseEvent.IsControlDown() && SlotType == ESlotType::Inventory)
	{
		// SelectOption ������ �������� �ʾҰų�, �̹� ����Ʈ�� �����ϸ� ����
		if (SelectOptionRef == nullptr || SelectOptionRef->IsInViewport())
			return ResultReply.NativeReply;

		FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
		FVector2D PixelPos;
		FVector2D ViewportPos;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), MousePos, PixelPos, ViewportPos);

		SelectOptionRef->SetPositionInViewport(ViewportPos + FVector2D(-40.f, -10.f), false);
		SelectOptionRef->SetTargetSlot(this);
		SelectOptionRef->AddToViewport();

		ResultReply.NativeReply = FReply::Handled();
	}

	return ResultReply.NativeReply;
}


void USlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// �巡�׽� ���̴� Visual ����
	UDragVisual* DragVisual = CreateWidget<UDragVisual>(this, DragVisualClass);
	if (DragVisual == nullptr)
		return;
	DragVisual->SetVisual(Item->ItemImage);

	// ���� ���
	if (ClickSound) PlaySound(ClickSound);

	// �巡�� ������ ������ Operation ����
	UDragDropOperation* DragOperation = Cast<UDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass()));
	if (DragOperation == nullptr)
		return;
	DragOperation->DefaultDragVisual = DragVisual;
	DragOperation->Payload = this;

	OutOperation = DragOperation;
}


bool USlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// �巡���� ������ USlot Ÿ������ ĳ���� & ��ȿ���� üũ
	USlot* DragSlot = Cast<USlot>(InOperation->Payload);
	if (DragSlot == nullptr)
		return false;

	// �������� ��ġ�� ������ �ڱ��ڽŰ� ���ٸ� ����
	if (DragSlot == this)
		return false;

	// - OnlySee Ÿ���� ������ ���⸸ �����ϹǷ� ����
	// - Equipment Ÿ���� ������ �巡�׸� ������� �ʰ� ��Ŭ���� ���
	if (SlotType == ESlotType::OnlySee || SlotType == ESlotType::Equipment) return false;

	UItem* DragItem = DragSlot->Item;
	if (DragItem == nullptr)
		return false;

	// * Drop�� ���� ������ �� �Ʒ��� �ۼ�

	// < ���� ���� >
	//  1) ��� ������ ����ִ� ���
	//  2) ���� �ٸ� ���� ItemName�� ���� ���
	//  3) ��� ������ ���������� �������
	if (Item == nullptr
		|| DragItem->ItemName != Item->ItemName
		|| DragSlot->Count >= DragItem->MaxCount
		|| Count >= Item->MaxCount)
	{
		// [����] - QuickSlot Ÿ���� ������ PotionŸ���� �����۸� �������
		if (SlotType == ESlotType::QuickSlot && DragItem->ItemType != EItemType::Potion)
			return false;

		SwapSlot(DragSlot);
	}
	// < ����ó�� ���� >
	//  1) �巡���Ϸ��� �������� ������ �ִ밡 �ƴϰ�, ��� ��ġ�� �ִ� �����۵� ������ �ִ밡 �ƴѰ��
	//	   - �������� ��ħ (������ �Ѱų� 0�� �Ʒ��� ������ ���� �Լ� ���ο��� ó��)
	else
	{
		int32 Remainder = DragSlot->Count + Count - Item->MaxCount;
		SetCount(DragSlot->Count + Count);
		DragSlot->SetCount(Remainder);
	}

	return Result;
}


void USlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Outline->SetBrushColor(HighlightColor);
}


void USlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Outline->SetBrushColor(OriginColor);
}


void USlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	Outline->SetBrushColor(HighlightColor);
}


void USlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	Outline->SetBrushColor(OriginColor);
}


void USlot::SetSlot(UItem* NewItem, int32 NewCount)
{
	// 0�� ������ ������ �ްų�, �������� ���°�� ���� �ʱ�ȭ
	if (NewCount <= 0 || NewItem == nullptr)
	{
		ClearSlot();
		return;
	}
	// �������� �Ѱܹ������
	else
	{
		Item = NewItem;
		Img_Item->SetBrushFromTexture(NewItem->ItemImage, false);
		Img_Item->SetOpacity(1.f);

		// ������ ���� ����
		// * �ִ� �������� ������ 1������ ������ ������ ǥ��
		Count = FMath::Clamp(NewCount, 1, Item->MaxCount);
		if (Item->MaxCount > 1)
		{
			Text_Count->SetText(FText::AsNumber(Count));
		}
		// * �ִ� �������� ������ 1���� ������ ǥ������ ����
		else
		{
			Text_Count->SetText(FText());
		}
	}

}


void USlot::SetCount(int32 NewCount)
{
	// �������� ���°�� �������� ����
	if (Item == nullptr)
		return;

	Count = NewCount;
	Count = FMath::Clamp(Count, 0, Item->MaxCount);

	// ī��Ʈ�� 0�Ʒ��� ������ ��쿡�� ������ �������
	if (Count <= 0)
	{
		ClearSlot();
		return;
	}

	// ī��Ʈ�� ǥ���ϴ� Text ����
	Text_Count->SetText(FText::AsNumber(Count));
}


void USlot::AddCount(int32 Amount)
{
	// �������� ���°�� �������� ����
	if (Item == nullptr)
		return;

	SetCount(Count + Amount);
}


void USlot::ClearSlot()
{
	Item = nullptr;
	Count = 0;
	Img_Item->SetBrushFromTexture(nullptr);
	Img_Item->SetOpacity(0.f);
	Text_Count->SetText(FText());
}


void USlot::SwapSlot(USlot* NewSlot)
{
	// ������ �Ѱܹ��� ���Ѱ�� ������ ����
	if (NewSlot == nullptr)
		return;

	// �������� ���� Swap -> �����ۿ� ���� null üũ�� SetSlot���� ����
	UItem* Temp = Item;
	int32 TempCount = Count;

	SetSlot(NewSlot->Item, NewSlot->Count);
	NewSlot->SetSlot(Temp, TempCount);
}


void USlot::HideItemCount(bool Flag)
{
	if (Flag)
	{
		Text_Count->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Text_Count->SetVisibility(ESlateVisibility::Visible);
	}
}


bool USlot::IsEmptySlot()
{
	return (Item == nullptr) ? true : false;
}


UItem* USlot::GetSlotItem()
{
	return Item;
}


int32 USlot::GetItemCount()
{
	return Count;
}


UWidget* USlot::TooltipUpdate()
{
	// �������� �������� �ʰų� ���������� �������� �ʾ����� ����
	if (Item == nullptr || TooltipWidgetRef == nullptr)
		return nullptr;

	// Tooltip ���� ����
	TooltipWidgetRef->SetTooltipItem(Item);
	return TooltipWidgetRef;
}