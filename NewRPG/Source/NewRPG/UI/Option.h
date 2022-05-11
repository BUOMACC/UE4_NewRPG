// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Option.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UOption : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* DropDown_Shadow;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* DropDown_AntiAliasing;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* DropDown_PostProcessing;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Close;

protected:
	UFUNCTION()
	void OnSelected_Shadow(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnSelected_AntiAliasing(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnSelected_PostProcessing(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnClick_CloseButton();

	UFUNCTION()
	int32 ConvertQuality(FString& In);
};
