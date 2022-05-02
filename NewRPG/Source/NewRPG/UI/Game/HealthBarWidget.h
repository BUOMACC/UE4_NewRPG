// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetOwnerEntity(class AEntity* Owner) { OwnerEntity = Owner; }

private:
	UPROPERTY()
	class AEntity* OwnerEntity;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_EntityName;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HealthBar_Back;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HealthBar_Front;

private:
	void RefreshHealthBar();
};
