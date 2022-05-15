// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Controller/PlayerGameController.h"
#include "Entity/Player/BasePlayer.h"
#include "KIsmet/Gameplaystatics.h"
#include "UI/Game/DungeonMenu.h"
#include "UI/Game/HudWidget.h"
#include "UI/Game/StatusWidget.h"
#include "UI/Game/QuickSlot.h"
#include "UI/Main/Inventory/EquipSlot.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/Slot.h"
#include "UI/Main/Shop.h"
#include "UI/LoadingScreen.h"
#include "UI/Option.h"
#include "GameData.h"


void APlayerGameController::BeginPlay()
{
	Super::BeginPlay();

	// InputMode Setting
	FInputModeGameOnly InputMode;
	SetShowMouseCursor(false);
	SetInputMode(InputMode);

	// HudWidget�� ���ٸ� ������ ������
	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
		ShowHud(true);
	}

	// * DungeonMenu Widget ����
	if (DungeonMenuClass)
	{
		DungeonMenu = CreateWidget<UDungeonMenu>(this, DungeonMenuClass);
	}

	// * Shop Widget ����
	if (ShopClass)
	{
		ShopWidget = CreateWidget<UShop>(this, ShopClass);
	}

	// LoadingScreen�� ���ٸ� ����
	if (LoadingClass)
	{
		LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingClass);
	}

	// OptionWidget�� ���ٸ� ����
	if (OptionClass)
	{
		OptionWidget = CreateWidget<UOption>(this, OptionClass);
	}
}


void APlayerGameController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// �����ϸ� ���ݵ��� ����
	ApplyStat();

	// �ʻ�ȭ ����
	ABasePlayer* OwningPlayer = Cast<ABasePlayer>(GetCharacter());
	if (OwningPlayer)
	{
		GetStatusWidget()->SetPortrait(OwningPlayer->GetPortrait());
		GetEquipSlot()->SetPortrait(OwningPlayer->GetPortrait());
	}
}


void APlayerGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("QuickSlot_0"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot0);
	InputComponent->BindAction(TEXT("QuickSlot_1"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot1);
	InputComponent->BindAction(TEXT("QuickSlot_2"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot2);
	InputComponent->BindAction(TEXT("QuickSlot_3"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot3);
	InputComponent->BindAction(TEXT("Option"), EInputEvent::IE_Pressed, this, &APlayerGameController::OpenOption);
}


void APlayerGameController::ApplyStat()
{
	ABasePlayer* OwningPlayer = Cast<ABasePlayer>(GetCharacter());
	if (OwningPlayer)
	{
		OwningPlayer->SettingExtraStat();
	}
}


void APlayerGameController::ShowInventory()
{
	HudWidget->ShowInventory(true);
	HudWidget->ShowEquipSlot(true);
	AddUIStack(2);
}


void APlayerGameController::OpenDungeonMenu()
{
	if (DungeonMenu == nullptr && DungeonMenu->IsInViewport()) return;

	FVector2D Pos = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	DungeonMenu->SetDesiredSizeInViewport(FVector2D(1200, 700));
	DungeonMenu->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	DungeonMenu->SetPositionInViewport(Pos / 2, true);
	DungeonMenu->AddToViewport();
	AddUIStack(1);
}


void APlayerGameController::OpenShop(class UDataTable* ShopTable)
{
	if (ShopTable == nullptr || ShopWidget == nullptr || ShopWidget->IsInViewport()) return;

	FVector2D Pos = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	ShopWidget->SetDesiredSizeInViewport(FVector2D(800, 600));
	ShopWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	ShopWidget->SetPositionInViewport(Pos / 2, true);
	ShopWidget->ShopTable = ShopTable;
	ShopWidget->AddToViewport();
	AddUIStack(1);
}



void APlayerGameController::OpenLoadingScreen(FName LevelName, float WaitTime)
{
	if (LoadingScreen == nullptr) return;

	LoadingScreen->AddToViewport();
	LoadingScreen->StartLoading(LevelName, WaitTime);
	AddUIStack(1);
}


void APlayerGameController::OpenOption()
{
	if (OptionWidget == nullptr) return;

	OptionWidget->AddToViewport();
	AddUIStack(1);
}


void APlayerGameController::UseQuickSlot0()
{
	if (HudWidget == nullptr) return;

	HudWidget->QuickSlot->UseQuickSlot(0);
}


void APlayerGameController::UseQuickSlot1()
{
	if (HudWidget == nullptr) return;

	HudWidget->QuickSlot->UseQuickSlot(1);
}


void APlayerGameController::UseQuickSlot2()
{
	if (HudWidget == nullptr) return;

	HudWidget->QuickSlot->UseQuickSlot(2);
}


void APlayerGameController::UseQuickSlot3()
{
	if (HudWidget == nullptr) return;

	HudWidget->QuickSlot->UseQuickSlot(3);
}


void APlayerGameController::ShowHud(bool Show)
{
	// ǥ���ϱ�� �ߴٸ� Viewport�� �߰��Ǿ����� ���� ��쿡�� �����ݴϴ�.
	if (Show)
	{
		if (HudWidget->IsInViewport()) return;
		HudWidget->AddToViewport();
	}
	// ǥ������ �ʱ�� �ߴٸ� �̹� Viewport�� �߰��� ��쿡�� RemoveFromParent �մϴ�.
	else
	{
		if (!HudWidget->IsInViewport()) return;
		HudWidget->RemoveFromParent();
	}
}


void APlayerGameController::ShowInteractMark(bool Show)
{
	if (HudWidget == nullptr) return;
	HudWidget->ShowInteractMark(Show);
}


void APlayerGameController::NewOpenLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Field"), false);
}


void APlayerGameController::AddUIStack(int32 Amount)
{
	UIStack += Amount;
	UIStack = FMath::Clamp(UIStack, 0, 99);

	// Stack�� 0�� �Ǿ��ٸ� ��� UI�� �����ٴ� �ǹ�
	if (UIStack <= 0)
	{
		UIStack = 0;

		FInputModeGameOnly InputMode;
		SetShowMouseCursor(false);
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeUIOnly InputMode;
		SetShowMouseCursor(true);
		SetInputMode(InputMode);
	}
}