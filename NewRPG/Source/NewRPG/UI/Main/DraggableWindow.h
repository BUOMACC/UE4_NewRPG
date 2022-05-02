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
	bool bDragging;		// 드래그 중인지를 의미
	FVector2D MouseGap;	// 마우스를 창의 어느 위치에서 드래그했는지의 간격

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TabName;

	UPROPERTY()
	class UUserWidget* TWidget; // 드래그하려는 대상 Widget

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Close;
};
