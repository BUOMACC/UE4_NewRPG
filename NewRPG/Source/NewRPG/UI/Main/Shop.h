// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Shop.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UShop : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere)
	class UDataTable* ShopTable;

protected:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ShopElements;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Close;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UShopElement> ElementClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMessageBox> MessageClass;
	
	UPROPERTY()
	class UMessageBox* MessageWidget;

protected:
	UFUNCTION()
	void OnClick_CloseButton();

	// 구매하려는 아이템 선택
	UFUNCTION()
	void SelectElement(class UShopElement* Element);

	// 선택한 아이템 구매요청을 처리
	UFUNCTION()
	void ProcessSelectedElement();

	UFUNCTION()
	FText UpdateGoldText();

private:
	class UShopElement* SelectedElement;
};
