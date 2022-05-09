// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ComboElement.generated.h"

USTRUCT(BlueprintType)
struct FComboElement
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ComboAnimation;

	UPROPERTY(EditAnywhere)
	float MPCost;

	UPROPERTY(EditAnywhere)
	int32 NextComboIndexL;

	UPROPERTY(EditAnywhere)
	int32 NextComboIndexR;
};
