// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableWindow.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"


void UDraggableWindow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	MoveWindowToMousePosition();
}


void UDraggableWindow::SetDraggableWindow(FText TabName, UUserWidget* TargetWidget)
{
	Text_TabName->SetText(TabName);
	TWidget = TargetWidget;
}


FReply UDraggableWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (!bDragging && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// 드래그중으로 변경
		bDragging = true;
		if (OnDragWindowClick.IsBound())
			OnDragWindowClick.Execute(TWidget);

		// 마우스 좌표를 뷰포트 좌표로 변환해 저장
		FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
		FVector2D PixelPos;
		FVector2D ViewportPos;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), MousePos, PixelPos, ViewportPos);

		// 클릭한 위치와 위젯의 위치를 뺀 간격을 저장함
		FVector2D WidgetPos = UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->GetPosition();
		MouseGap = ViewportPos - WidgetPos;
	}
	
	return FReply::Handled();
}


FReply UDraggableWindow::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (bDragging)
	{
		bDragging = false;
	}

	return FReply::Handled();
}


void UDraggableWindow::MoveWindowToMousePosition()
{
	if (bDragging)
	{
		// 뷰포트 좌표로 변환된 위치에서 마우스 클릭을 했던 지점을 빼 클릭위치를 유지
		FVector2D TargetPosition;
		TargetPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - MouseGap;

		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(TargetPosition);
	}
}