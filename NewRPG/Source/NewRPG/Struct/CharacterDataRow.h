// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CharacterDataRow.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataRow : public FTableRowBase
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

	// 기본 이동속도
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

	// 공격모드 -> 기본모드로 전환할때 실행되는 애니메이션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* TravelStartMontage;

	// 공격모드 이동속도
	UPROPERTY(EditAnywhere)
	float BattleMoveSpd;

	// 구르는 속도 (0 = Default, 20 = 20% Fast)
	UPROPERTY(EditAnywhere)
	float RollingSpeed;

	// 구르는 속도
	UPROPERTY(EditAnywhere)
	float RollingMoveSpeed;

	// 구를때(회피) 애니메이션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* RollingMontage;

	// 구를때 소모되는 스테미나
	UPROPERTY(EditAnywhere)
	float RollingDecStamina;
		
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
