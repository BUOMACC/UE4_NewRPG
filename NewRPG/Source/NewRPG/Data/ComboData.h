// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/ComboElement.h"
#include "ComboData.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UComboData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FComboElement> ComboList;
};
