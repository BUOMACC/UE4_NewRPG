// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectButton.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UCharacterSelectButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* Outline;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Portrait;

	// 버튼에 마우스를 가져다댔을 때 테두리 색상 변경효과
	UPROPERTY(EditAnywhere)
	FLinearColor OriginColor;

	UPROPERTY(EditAnywhere)
	FLinearColor HighlightColor;

public:
	UPROPERTY(EditAnywhere)
	class UTexture2D* CharacterIcon;
};
