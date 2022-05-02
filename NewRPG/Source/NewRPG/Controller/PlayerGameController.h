// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/Game/HudWidget.h"
#include "PlayerGameController.generated.h"

class UInventory;
class UQuickSlot;
class UEquipSlot;
class USlot;

/**
 * 
 */
UCLASS()
class NEWRPG_API APlayerGameController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetupInputComponent() override;

private:
	// �÷��̾ ����� HUD
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UHudWidget> HudWidgetClass;
	UHudWidget* HudWidget;

	int32 UIStack;	// UI�� ��������, 0�̵Ǹ� ������ �÷����� �� �ִ� ȯ��(���콺 Ŀ��ǥ�� ...)

protected:
	void UseQuickSlot0();
	void UseQuickSlot1();
	void UseQuickSlot2();
	void UseQuickSlot3();
	void NewOpenLevel();

public:
	void ApplyStat();	// ���ǽ� ������ ������ �߰������� ���ݿ� ����
	void ShowHud(bool Show);
	void ShowInteractMark(bool Show);
	void ShowInventory();
	void OpenDungeonMenu();
	void OpenShop();
	void AddUIStack(int32 Amount);

	UFUNCTION(BlueprintPure)
	UHudWidget* GetHudWidget() { return HudWidget; }

	UFUNCTION(BlueprintPure)
	UInventory* GetInventory() { return HudWidget->Inventory; }

	UFUNCTION(BlueprintPure)
	UQuickSlot* GetQuickSlot() { return HudWidget->QuickSlot; }

	UFUNCTION(BlueprintPure)
	UEquipSlot* GetEquipSlot() { return HudWidget->EquipSlot; }
};