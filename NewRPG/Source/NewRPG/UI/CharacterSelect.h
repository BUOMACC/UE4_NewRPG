// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelect.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UCharacterSelect : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CharacterName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CharacterDesc;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Next;

protected:
	UFUNCTION()
	FText UpdateCharacterNameText();

	UFUNCTION()
	FText UpdateCharacterDescText();

	UFUNCTION()
	void OnClick_Next();
};
