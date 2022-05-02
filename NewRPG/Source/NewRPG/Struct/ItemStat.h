#pragma once

#include "ItemStat.generated.h"


USTRUCT(BlueprintType)
struct FItemStat
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Health = 0.f;		// ü��

	UPROPERTY(EditAnywhere)
	float Strength = 0.f;	// ���ݷ�

	UPROPERTY(EditAnywhere)
	float Defence = 0.f;	// ���� 100 = 100%

	UPROPERTY(EditAnywhere)
	float CritChance = 0.f;	// ũ��Ƽ�� Ȯ�� 100 = 100%

	UPROPERTY(EditAnywhere)
	float AttackSpd = 0.f;	// ���ݼӵ� 0 = 0% ����

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