// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlayerGameController.h"
#include "Entity/Player/BasePlayer.h"
#include "KIsmet/Gameplaystatics.h"
#include "UI/Game/HudWidget.h"
#include "UI/Game/QuickSlot.h"
#include "UI/Main/Inventory/EquipSlot.h"
#include "UI/Main/Inventory/Inventory.h"
#include "UI/Main/Inventory/Slot.h"
#include "GameData.h"


void APlayerGameController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// 빙의하면 HUD를 보여주고 스텟들을 적용
	ShowHud(true);
	ApplyStat();
}


void APlayerGameController::OnUnPossess()
{
	Super::OnUnPossess();

	ShowHud(false);
}


void APlayerGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerGameController::NewOpenLevel);
	InputComponent->BindAction(TEXT("QuickSlot_0"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot0);
	InputComponent->BindAction(TEXT("QuickSlot_1"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot1);
	InputComponent->BindAction(TEXT("QuickSlot_2"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot2);
	InputComponent->BindAction(TEXT("QuickSlot_3"), EInputEvent::IE_Pressed, this, &APlayerGameController::UseQuickSlot3);
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
	FInputModeUIOnly InputMode;
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
}


void APlayerGameController::OpenDungeonMenu()
{
	HudWidget->OpenDungeonMenu();
	AddUIStack(1);
	FInputModeUIOnly InputMode;
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
}


void APlayerGameController::OpenShop()
{
	HudWidget->OpenShop();
	AddUIStack(1);
	FInputModeUIOnly InputMode;
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
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
	if (HudWidgetClass == nullptr) return;

	// HudWidget이 없다면 생성
	if (!HudWidget && HudWidgetClass)
	{
		HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
	}

	// 표시하기로 했다면 Viewport에 추가되어있지 않은 경우에만 보여줍니다.
	if (Show)
	{
		if (HudWidget->IsInViewport()) return;
		HudWidget->AddToViewport();
	}
	// 표시하지 않기로 했다면 이미 Viewport에 추가된 경우에만 RemoveFromParent 합니다.
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

	// Stack이 0이 되었다면 모든 UI가 닫혔다는 의미
	if (UIStack <= 0)
	{
		UIStack = 0;

		FInputModeGameOnly InputMode;
		SetShowMouseCursor(false);
		SetInputMode(InputMode);
	}
}