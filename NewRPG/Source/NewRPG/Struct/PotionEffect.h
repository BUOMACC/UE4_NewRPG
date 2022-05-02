#pragma once

#include "PotionEffect.generated.h"


USTRUCT(BlueprintType)
struct FPotionEffect
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float HealHP;

	UPROPERTY(EditAnywhere)
	float HealHP_Ratio;	// HP���� ����(100 = 100%)

	UPROPERTY(EditAnywhere)
	float HealMP;

	UPROPERTY(EditAnywhere)
	float HealMP_Ratio; // MP���� ����(100 = 100%)

	UPROPERTY(EditAnywhere)
	float HealStamina;
};