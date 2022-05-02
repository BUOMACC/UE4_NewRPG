// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWindow.generated.h"


DECLARE_DELEGATE_OneParam(FOnDragWindowClick, UUserWidget*);

UCLASS()
class NEWRPG_API UDraggableWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// *** Delegate ***
	FOnDragWindowClick OnDragWindowClick;

public:
	UFUNCTION(BlueprintCallable)
	void SetDraggableWindow(FText Name, UUserWidget* TWidget);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION(BlueprintCallable)
	void MoveWindowToMousePosition();

private:
	bool bDragging;		// �巡�� �������� �ǹ�
	FVector2D MouseGap;	// ���콺�� â�� ��� ��ġ���� �巡���ߴ����� ����

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TabName;

	UPROPERTY()
	class UUserWidget* TWidget; // �巡���Ϸ��� ��� Widget

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Close;
};
