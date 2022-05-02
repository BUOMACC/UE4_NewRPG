// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NameTag.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UNameTag : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_NameTag;

public:
	UFUNCTION(BlueprintCallable)
	void SetNameTag(FString& Name);
};
