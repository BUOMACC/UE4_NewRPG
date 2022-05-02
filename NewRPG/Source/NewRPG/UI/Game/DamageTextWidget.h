// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Damage;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* OutAnim;

	UPROPERTY(EditAnywhere)
	FSlateColor NormalColor;

	UPROPERTY(EditAnywhere)
	FSlateColor CriticalColor;

public:
	void SetDamageText(float Amount, bool bIsCritical);
};
