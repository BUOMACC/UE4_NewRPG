// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "EnemyDataRow.generated.h"

USTRUCT(BlueprintType)
struct FEnemyDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Strength;

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float Mana;

	UPROPERTY(EditAnywhere)
	float Stamina;

	// 이동속도
	UPROPERTY(EditAnywhere)
	float MoveSpd;

	// 기본 방어력
	UPROPERTY(EditAnywhere)
	float Defence;

	// 기본 크리티컬 확률
	UPROPERTY(EditAnywhere)
	float CritChance;

	// 기본 공격속도
	UPROPERTY(EditAnywhere)
	float AttackSpeed;
		
	// 무적인지
	UPROPERTY(EditAnywhere)
	bool Invincible;

	// 슈퍼아머 상태인지
	UPROPERTY(EditAnywhere)
	bool SuperArmor;

	// 피격 애니메이션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* HitMontage;
};
