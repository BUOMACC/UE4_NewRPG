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

	// Tooltip Widget 생성
	TooltipWidgetRef = CreateWidget<UTooltip>(this, TooltipClass);

	// SelectOption Widget 생성
	SelectOptionRef = CreateWidget<USelectOption>(this, SelectOptionClass);

	Img_Item->SynchronizeProperties();
	Outline->SetBrushColor(OriginColor);
}


FReply USlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply ResultReply;
	ResultReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 아이템이 없는경우 종료
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

	// * 이곳에 마우스 좌클릭에 대한 로직 작성

	// - OnlySee 타입의 슬롯은 보기만 가능하므로 종료
	// - Equipment 타입의 슬롯은 드래그를 허용하지 않고 우클릭만 허용
	if (SlotType == ESlotType::OnlySee || SlotType == ESlotType::Equipment)
		return ResultReply.NativeReply;

	// 드래그 감지
	ResultReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	return ResultReply.NativeReply;
}


FReply USlot::OnRightMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply ResultReply;
	ResultReply.NativeReply = FReply::Unhandled();

	// * 이곳에 마우스 우클릭에 대한 로직 작성
	
	// [Equipment] : RightClick - 장비 착용해제
	if (SlotType == ESlotType::Equipment && OnUnEquipItem.IsBound())
	{
		OnUnEquipItem.Execute(this);
	}
	
	// [Inventory] : Ctrl + RightClick - 아이템에 대한 선택옵션 (장착, 버리기..) 표시
	if (InMouseEvent.IsControlDown() && SlotType == ESlotType::Inventory)
	{
		// SelectOption 위젯이 생성되지 않았거나, 이미 뷰포트에 존재하면 중지
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

	// 드래그시 보이는 Visual 설정
	UDragVisual* DragVisual = CreateWidget<UDragVisual>(this, DragVisualClass);
	if (DragVisual == nullptr)
		return;
	DragVisual->SetVisual(Item->ItemImage);

	// 사운드 재생
	if (ClickSound) PlaySound(ClickSound);

	// 드래그 정보를 저장할 Operation 설정
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

	// 드래그한 슬롯을 USlot 타입으로 캐스팅 & 유효한지 체크
	USlot* DragSlot = Cast<USlot>(InOperation->Payload);
	if (DragSlot == nullptr)
		return false;

	// 놓으려는 위치의 슬롯이 자기자신과 같다면 종료
	if (DragSlot == this)
		return false;

	// - OnlySee 타입의 슬롯은 보기만 가능하므로 종료
	// - Equipment 타입의 슬롯은 드래그를 허용하지 않고 우클릭만 허용
	if (SlotType == ESlotType::OnlySee || SlotType == ESlotType::Equipment) return false;

	UItem* DragItem = DragSlot->Item;
	if (DragItem == nullptr)
		return false;

	// * Drop에 대한 로직은 이 아래에 작성

	// < 스왑 조건 >
	//  1) 대상 슬롯이 비어있는 경우
	//  2) 서로 다른 고유 ItemName을 가진 경우
	//  3) 어느 한쪽이 보유개수를 넘은경우
	if (Item == nullptr
		|| DragItem->ItemName != Item->ItemName
		|| DragSlot->Count >= DragItem->MaxCount
		|| Count >= Item->MaxCount)
	{
		// [예외] - QuickSlot 타입의 슬롯은 Potion타입의 아이템만 스왑허용
		if (SlotType == ESlotType::QuickSlot && DragItem->ItemType != EItemType::Potion)
			return false;

		SwapSlot(DragSlot);
	}
	// < 개수처리 조건 >
	//  1) 드래그하려는 아이템의 수량이 최대가 아니고, 드랍 위치에 있는 아이템도 수량이 최대가 아닌경우
	//	   - 아이템을 합침 (수량이 넘거나 0개 아래로 내려간 경우는 함수 내부에서 처리)
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
	// 0개 이하의 개수를 받거나, 아이템이 없는경우 슬롯 초기화
	if (NewCount <= 0 || NewItem == nullptr)
	{
		ClearSlot();
		return;
	}
	// 아이템을 넘겨받은경우
	else
	{
		Item = NewItem;
		Img_Item->SetBrushFromTexture(NewItem->ItemImage, false);
		Img_Item->SetOpacity(1.f);

		// 아이템 개수 설정
		// * 최대 보유가능 개수가 1개보다 많으면 개수를 표시
		Count = FMath::Clamp(NewCount, 1, Item->MaxCount);
		if (Item->MaxCount > 1)
		{
			Text_Count->SetText(FText::AsNumber(Count));
		}
		// * 최대 보유가능 개수가 1보다 작으면 표시하지 않음
		else
		{
			Text_Count->SetText(FText());
		}
	}

}


void USlot::SetCount(int32 NewCount)
{
	// 아이템이 없는경우 동작하지 않음
	if (Item == nullptr)
		return;

	Count = NewCount;
	Count = FMath::Clamp(Count, 0, Item->MaxCount);

	// 카운트가 0아래로 내려간 경우에는 슬롯을 비워버림
	if (Count <= 0)
	{
		ClearSlot();
		return;
	}

	// 카운트를 표시하는 Text 갱신
	Text_Count->SetText(FText::AsNumber(Count));
}


void USlot::AddCount(int32 Amount)
{
	// 아이템이 없는경우 동작하지 않음
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
	// 슬롯을 넘겨받지 못한경우 실행을 무시
	if (NewSlot == nullptr)
		return;

	// 아이템을 서로 Swap -> 아이템에 대한 null 체크는 SetSlot에서 진행
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
	// 아이템이 존재하지 않거나 툴팁위젯이 생성되지 않았으면 종료
	if (Item == nullptr || TooltipWidgetRef == nullptr)
		return nullptr;

	// Tooltip 위젯 설정
	TooltipWidgetRef->SetTooltipItem(Item);
	return TooltipWidgetRef;
}