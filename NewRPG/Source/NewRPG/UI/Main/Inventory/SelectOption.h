// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectOption.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API USelectOption : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTargetSlot(USlot* Target);

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Equip;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Destroy;

protected:
	UFUNCTION()
	void OnClick_EquipButton();

	UFUNCTION()
	void OnClick_DestroyButton();

private:
	class USlot* TargetSlot;
};
