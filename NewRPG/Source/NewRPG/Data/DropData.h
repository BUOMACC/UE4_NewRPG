// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/DropInfo.h"
#include "Engine/DataAsset.h"
#include "DropData.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UDropData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FDropInfo> Drops;
};
