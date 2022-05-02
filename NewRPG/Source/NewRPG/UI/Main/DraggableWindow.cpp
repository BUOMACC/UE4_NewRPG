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
		// �巡�������� ����
		bDragging = true;
		if (OnDragWindowClick.IsBound())
			OnDragWindowClick.Execute(TWidget);

		// ���콺 ��ǥ�� ����Ʈ ��ǥ�� ��ȯ�� ����
		FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
		FVector2D PixelPos;
		FVector2D ViewportPos;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), MousePos, PixelPos, ViewportPos);

		// Ŭ���� ��ġ�� ������ ��ġ�� �� ������ ������
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
		// ����Ʈ ��ǥ�� ��ȯ�� ��ġ���� ���콺 Ŭ���� �ߴ� ������ �� Ŭ����ġ�� ����
		FVector2D TargetPosition;
		TargetPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - MouseGap;

		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(TargetPosition);
	}
}