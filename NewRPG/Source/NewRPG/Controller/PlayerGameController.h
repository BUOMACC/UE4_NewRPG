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
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

private:
	// �÷��̾ ����� HUD
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UHudWidget> HudWidgetClass;

	UPROPERTY()
	UHudWidget* HudWidget;

	// ��������� �����ִ� ȭ��
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UDungeonMenu> DungeonMenuClass;

	UPROPERTY()
	class UDungeonMenu* DungeonMenu;

	// Shop
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UShop> ShopClass;

	UPROPERTY()
	class UShop* ShopWidget;

	// �ε��� ���� ȭ��
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class ULoadingScreen> LoadingClass;

	UPROPERTY()
	class ULoadingScreen* LoadingScreen;

	// �ɼ� ȭ��
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UOption> OptionClass;

	UPROPERTY()
	class UOption* OptionWidget;

	int32 UIStack;	// UI�� ��������, 0�̵Ǹ� ������ �÷����� �� �ִ� ȯ��(���콺 Ŀ��ǥ�� ...)

protected:
	void UseQuickSlot0();
	void UseQuickSlot1();
	void UseQuickSlot2();
	void UseQuickSlot3();

public:
	void ApplyStat();	// ���ǽ� ������ ������ �߰������� ���ݿ� ����

	// * Show : Collapsed / Visibility�� ���� ǥ��
	// * Open : AddToViewport�� ���� ǥ��
	void ShowHud(bool Show);
	void ShowInteractMark(bool Show);
	void ShowInventory();
	void OpenDungeonMenu();
	void OpenShop(class UDataTable* ShopTable);
	void OpenLoadingScreen(FName LevelName, float WaitTime);
	void OpenOption();
	void AddUIStack(int32 Amount);

	UFUNCTION(BlueprintPure)
	UHudWidget* GetHudWidget() { return HudWidget; }

	UFUNCTION(BlueprintPure)
	UStatusWidget* GetStatusWidget() { return HudWidget->StatusWidget; }

	UFUNCTION(BlueprintPure)
	UInventory* GetInventory() { return HudWidget->Inventory; }

	UFUNCTION(BlueprintPure)
	UQuickSlot* GetQuickSlot() { return HudWidget->QuickSlot; }

	UFUNCTION(BlueprintPure)
	UEquipSlot* GetEquipSlot() { return HudWidget->EquipSlot; }
};
