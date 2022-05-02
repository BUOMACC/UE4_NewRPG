// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UImage* Portrait;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* ManaBar;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* StaminaBar;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_CName;

	
private:
	UFUNCTION()
	float OnHealthBarChanged();

	UFUNCTION()
	float OnManaBarChanged();

	UFUNCTION()
	float OnStaminaBarChanged();

	UFUNCTION()
	FText OnCNameChanged();
};
