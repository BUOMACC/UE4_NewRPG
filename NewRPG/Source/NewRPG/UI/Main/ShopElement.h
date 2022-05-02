// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopElement.generated.h"


// ������ ���Ź�ư�� ���� ���Ÿ� �õ��Ҷ� �̺�Ʈ - Shop���� ó��
DECLARE_DELEGATE_OneParam(FOnSelectElement, UShopElement*);

UCLASS()
class NEWRPG_API UShopElement : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetElement(class UItem* Visual, FText Title, FText Desc, int32 Gold, int32 Cnt);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Desc;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Buy;

protected:
	UFUNCTION(BlueprintCallable)
	void OnClick_BuyItem();

public:
	FOnSelectElement OnSelectElement;

	UPROPERTY(meta = (BindWidget))
	class USlot* ItemVisual;

	UPROPERTY(BlueprintReadWrite)
	int32 Price;

	UPROPERTY(BlueprintReadWrite)
	int32 Count;
};
