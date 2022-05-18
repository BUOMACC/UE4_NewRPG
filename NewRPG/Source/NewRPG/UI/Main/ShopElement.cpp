// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopElement.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Item.h"
#include "UI/Main/Inventory/Slot.h"


void UShopElement::SetElement(UItem* Visual, FText Title, FText Desc, int32 Gold, int32 Cnt)
{
	ItemVisual->SetSlot(Visual, Cnt);
	ItemVisual->HideItemCount(true);
	Text_Title->SetText(Title);
	Text_Desc->SetText(Desc);
	Text_Gold->SetText(FText::AsNumber(Gold));

	Price = Gold;
	Count = Cnt;
	Btn_Buy->OnClicked.AddDynamic(this, &UShopElement::OnClick_BuyItem);
}


void UShopElement::OnClick_BuyItem()
{
	if (ItemVisual->GetSlotItem() && OnSelectElement.IsBound())
	{
		OnSelectElement.Execute(this);
	}
}