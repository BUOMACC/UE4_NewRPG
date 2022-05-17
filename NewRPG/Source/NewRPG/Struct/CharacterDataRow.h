// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CharacterDataRow.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Character Select Menu")
	FText SelectMenuName;

	UPROPERTY(EditAnywhere, Category = "Character Select Menu", meta = (MultiLine = "true"))
	FText SelectMenuDesc;

	UPROPERTY(EditAnywhere, Category = "Character Select Menu")
	TSubclassOf<class ABasePlayer> PreviewClass;

	UPROPERTY(EditAnywhere, Category = "Info")
	class UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Strength;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Mana;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Stamina;

	// 기본 이동속도
	UPROPERTY(EditAnywhere, Category = "Info")
	float MoveSpd;

	// 기본 방어력
	UPROPERTY(EditAnywhere, Category = "Info")
	float Defence;

	// 기본 크리티컬 확률
	UPROPERTY(EditAnywhere, Category = "Info")
	float CritChance;

	// 기본 공격속도
	UPROPERTY(EditAnywhere, Category = "Info")
	float AttackSpeed;

	// 공격모드 -> 기본모드로 전환할때 실행되는 애니메이션
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* TravelStartMontage;

	// 공격모드 이동속도
	UPROPERTY(EditAnywhere, Category = "Info")
	float BattleMoveSpd;

	// 구르는 속도 (0 = Default, 20 = 20% Fast)
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingSpeed;

	// 구르는 속도
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingMoveSpeed;

	// 구를때(회피) 애니메이션
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* RollingMontage;

	// 구를때 소모되는 스테미나
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingDecStamina;

	// 얼마나 스테미너를 사용하지 않아야 스테미너를 회복할지
	UPROPERTY(EditAnywhere, Category = "Info")
	float Heal_Stamina_Time;

	// 초당 회복하는 스테미너
	UPROPERTY(EditAnywhere, Category = "Info")
	float Heal_Stamina_PerSec;
		
	// 무적인지
	UPROPERTY(EditAnywhere, Category = "Info")
	bool Invincible;

	// 슈퍼아머 상태인지
	UPROPERTY(EditAnywhere, Category = "Info")
	bool SuperArmor;

	// 피격 애니메이션
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* HitMontage;

	// 피격 사운드
	UPROPERTY(EditAnywhere, Category = "Info")
	class USoundBase* HitSound;
};
