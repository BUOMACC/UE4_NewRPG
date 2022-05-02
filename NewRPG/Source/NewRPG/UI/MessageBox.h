// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageBox.generated.h"


DECLARE_DELEGATE(FOnOkButtonSelected);
DECLARE_DELEGATE(FOnCancelButtonSelected);

UCLASS()
class NEWRPG_API UMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Desc;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Ok;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Cancel;

protected:
	UFUNCTION()
	void OnClick_Ok();

	UFUNCTION()
	void OnClick_Cancel();

public:
	FOnOkButtonSelected OnOkButtonSelected;
	FOnCancelButtonSelected OnCancelButtonSelected;

	UFUNCTION(BlueprintCallable)
	void SetMessage(FText Title, FText Desc, bool HideCancelButton);
};
