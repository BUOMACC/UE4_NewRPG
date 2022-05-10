// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"


DECLARE_DELEGATE(FOnLoadingEnd);

UCLASS()
class NEWRPG_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartLoading(FName LevelName, float Time);
};
