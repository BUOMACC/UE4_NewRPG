#pragma once

#include "ItemStat.generated.h"


USTRUCT(BlueprintType)
struct FItemStat
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Health = 0.f;		// 체력

	UPROPERTY(EditAnywhere)
	float Strength = 0.f;	// 공격력

	UPROPERTY(EditAnywhere)
	float Defence = 0.f;	// 방어력 100 = 100%

	UPROPERTY(EditAnywhere)
	float CritChance = 0.f;	// 크리티컬 확률 100 = 100%

	UPROPERTY(EditAnywhere)
	float AttackSpd = 0.f;	// 공격속도 0 = 0% 증가

public:
	FItemStat()
	{
		Health = 0.f;
		Strength = 0.f;
		Defence = 0.f;
		CritChance = 0.f;
		AttackSpd = 0.f;
	}

	void operator+=(const FItemStat& Target)
	{
		Health = Health + Target.Health;
		Strength = Strength + Target.Strength;
		Defence = Defence + Target.Defence;
		CritChance = CritChance + Target.CritChance;
		AttackSpd = AttackSpd + Target.AttackSpd;
	}

	FItemStat operator+(const FItemStat& Target)
	{
		FItemStat Result;
		Result.Health = Health + Target.Health;
		Result.Strength = Strength + Target.Strength;
		Result.Defence = Defence + Target.Defence;
		Result.CritChance = CritChance + Target.CritChance;
		Result.AttackSpd = AttackSpd + Target.AttackSpd;

		return Result;
	}
};