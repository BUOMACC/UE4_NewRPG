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
	// 플레이어가 사용할 HUD
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UHudWidget> HudWidgetClass;

	UPROPERTY()
	UHudWidget* HudWidget;

	// 던전목록을 보여주는 화면
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UDungeonMenu> DungeonMenuClass;

	UPROPERTY()
	class UDungeonMenu* DungeonMenu;

	// Shop
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UShop> ShopClass;

	UPROPERTY()
	class UShop* ShopWidget;

	// 로딩시 사용될 화면
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class ULoadingScreen> LoadingClass;

	UPROPERTY()
	class ULoadingScreen* LoadingScreen;

	// 옵션 화면
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UOption> OptionClass;

	UPROPERTY()
	class UOption* OptionWidget;

	int32 UIStack;	// UI가 쌓인정도, 0이되면 게임을 플레이할 수 있는 환경(마우스 커서표시 ...)

protected:
	void UseQuickSlot0();
	void UseQuickSlot1();
	void UseQuickSlot2();
	void UseQuickSlot3();

public:
	void ApplyStat();	// 빙의시 장착한 장비들의 추가스텟을 스텟에 적용

	// * Show : Collapsed / Visibility를 통한 표시
	// * Open : AddToViewport를 통한 표시
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
