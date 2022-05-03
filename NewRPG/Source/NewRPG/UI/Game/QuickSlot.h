// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UQuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SlotBox;

	UPROPERTY()
	TArray<class USlot*> Slots;

public:
	UFUNCTION(BlueprintCallable)
	void UseQuickSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void SaveQuickSlot();

	UFUNCTION(BlueprintCallable)
	void LoadQuickSlot();
};
