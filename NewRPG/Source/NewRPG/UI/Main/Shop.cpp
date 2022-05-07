// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/PlayerGameController.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "Struct/ShopDataRow.h"
#include "UI/Item.h"
#include "UI/MessageBox.h"
#include "UI/Main/ShopElement.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Main/Inventory/Inventory.h"


void UShop::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// * Binding
	Btn_Close->OnClicked.AddDynamic(this, &UShop::OnClick_CloseButton);
	Text_Gold->TextDelegate.BindUFunction(this, TEXT("UpdateGoldText"));

	// * MessageBox 위젯 생성
	if (MessageClass)
	{
		MessageWidget = CreateWidget<UMessageBox>(this, MessageClass);
	}
}


void UShop::NativeConstruct()
{
	Super::NativeConstruct();

	// * ShopElement 생성
	UGameData* Data = Cast<UGameData>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (ShopTable == nullptr || Data == nullptr || ElementClass == nullptr) return;

	ShopElements->ClearChildren();
	TArray<FName> RowNames = ShopTable->GetRowNames();
	for (FName Name : RowNames)
	{
		// 필요한 정보 로드
		FShopDataRow* ShopRow = ShopTable->FindRow<FShopDataRow>(Name, TEXT(""));
		UShopElement* Element = CreateWidget<UShopElement>(this, ElementClass);
		UItem* ElementItem = Data->GetItemByName(ShopRow->ItemName);

		// ShopElement를 ListView에 포함시켜 보여줌
		if (Element && ElementItem)
		{
			FTextFormat TitleFormat = FTextFormat(FText::FromString(TEXT("{0} ×{1}")));
			FText ElementTitle = FText::Format(TitleFormat, ElementItem->DisplayName, ShopRow->Count);
			Element->SetElement(ElementItem, ElementTitle, ElementItem->ItemDesc, ShopRow->Price, ShopRow->Count);
			Element->OnSelectElement.BindUFunction(this, TEXT("SelectElement"));
			ShopElements->AddChild(Element);
		}
	}
}


void UShop::OnClick_CloseButton()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	RemoveFromParent();
}


void UShop::SelectElement(UShopElement* Element)
{
	if (Element == nullptr) return;

	SelectedElement = Element;
	if (!MessageWidget->IsInViewport())
	{
		// MessageBox 위치, 사이즈 조정
		FVector2D Pos = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
		MessageWidget->SetDesiredSizeInViewport(FVector2D(340, 170));
		MessageWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		MessageWidget->SetPositionInViewport(Pos / 2, true);

		// MessageBox 띄우기
		MessageWidget->OnOkButtonSelected.BindUFunction(this, TEXT("ProcessSelectedElement"));
		MessageWidget->SetMessage(FText::FromString(TEXT("상점")), FText::FromString(TEXT("정말로 아이템을 구매하시겠습니까?")), false);
		MessageWidget->AddToViewport();
	}
}


void UShop::ProcessSelectedElement()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC == nullptr) return;

	if (Data->Gold >= SelectedElement->Price)
	{
		// - 구매성공
		UInventory* Inventory = PC->GetInventory();
		UItem* NewItem = Data->GetItemByName(SelectedElement->ItemVisual->GetSlotItem()->ItemName);
		Inventory->AddInventory(NewItem, SelectedElement->Count);
		Data->Gold -= SelectedElement->Price;
	}
}


FText UShop::UpdateGoldText()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	if (Data)
	{
		FTextFormat Format = FTextFormat(FText::FromString(TEXT("{0}")));
		return FText::Format(Format, Data->Gold);
	}
	return FText::FromString(TEXT("0"));
}