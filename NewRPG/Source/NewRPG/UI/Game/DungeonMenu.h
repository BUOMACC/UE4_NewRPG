// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonMenu.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UDungeonMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* ImageSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Close;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Stage1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Start;

	int32 SelectStage;	// 선택한 스테이지

protected:
	UFUNCTION()
	void OnClick_CloseButton();

	UFUNCTION()
	void OnClick_Stage1();

	UFUNCTION()
	void OnClick_Start();
};
