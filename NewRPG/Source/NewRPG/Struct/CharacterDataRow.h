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

	// �⺻ �̵��ӵ�
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

	// ���ݸ�� -> �⺻���� ��ȯ�Ҷ� ����Ǵ� �ִϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimMontage* TravelStartMontage;

	// ���ݸ�� �̵��ӵ�
	UPROPERTY(EditAnywhere)
	float BattleMoveSpd;

	// ������ �ӵ� (0 = Default, 20 = 20% Fast)
	UPROPERTY(EditAnywhere)
	float RollingSpeed;

	// ������ �ӵ�
	UPROPERTY(EditAnywhere)
	float RollingMoveSpeed;

	// ������(ȸ��) �ִϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimMontage* RollingMontage;

	// ������ �Ҹ�Ǵ� ���׹̳�
	UPROPERTY(EditAnywhere)
	float RollingDecStamina;
		
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
