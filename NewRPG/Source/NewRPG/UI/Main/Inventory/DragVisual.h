// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragVisual.generated.h"


/**
 * 
 */
UCLASS()
class NEWRPG_API UDragVisual : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Visual;

public:
	UFUNCTION(BlueprintCallable)
	void SetVisual(UTexture2D* Texture);
};
