// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffIcon.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBuffIcon : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* Outline;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Duration;

	UPROPERTY(EditAnywhere)
	FLinearColor DebuffOutlineColor;

public:
	UFUNCTION(BlueprintCallable)
	void SetBuffData(class UBuffData* Data);

	UFUNCTION(BlueprintPure)
	UBuffData* GetBuffData() { return BuffData; }

	UFUNCTION(BlueprintCallable)
	void SetBuffIconDuration(float NewDuration) { Duration = NewDuration; }

private:
	float Duration;

	UPROPERTY()
	class UBuffData* BuffData;
};
