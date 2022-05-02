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

	// �̵��ӵ�
	UPROPERTY(EditAnywhere)
	float MoveSpd;

	// �⺻ ����
	UPROPERTY(EditAnywhere)
	float Defence;

	// �⺻ ũ��Ƽ�� Ȯ��
	UPROPERTY(EditAnywhere)
	float CritChance;

	// �⺻ ���ݼӵ�
	UPROPERTY(EditAnywhere)
	float AttackSpeed;
		
	// ��������
	UPROPERTY(EditAnywhere)
	bool Invincible;

	// ���۾Ƹ� ��������
	UPROPERTY(EditAnywhere)
	bool SuperArmor;

	// �ǰ� �ִϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimMontage* HitMontage;
};
