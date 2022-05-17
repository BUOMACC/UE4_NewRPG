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

	// �⺻ �̵��ӵ�
	UPROPERTY(EditAnywhere, Category = "Info")
	float MoveSpd;

	// �⺻ ����
	UPROPERTY(EditAnywhere, Category = "Info")
	float Defence;

	// �⺻ ũ��Ƽ�� Ȯ��
	UPROPERTY(EditAnywhere, Category = "Info")
	float CritChance;

	// �⺻ ���ݼӵ�
	UPROPERTY(EditAnywhere, Category = "Info")
	float AttackSpeed;

	// ���ݸ�� -> �⺻���� ��ȯ�Ҷ� ����Ǵ� �ִϸ��̼�
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* TravelStartMontage;

	// ���ݸ�� �̵��ӵ�
	UPROPERTY(EditAnywhere, Category = "Info")
	float BattleMoveSpd;

	// ������ �ӵ� (0 = Default, 20 = 20% Fast)
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingSpeed;

	// ������ �ӵ�
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingMoveSpeed;

	// ������(ȸ��) �ִϸ��̼�
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* RollingMontage;

	// ������ �Ҹ�Ǵ� ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Info")
	float RollingDecStamina;

	// �󸶳� ���׹̳ʸ� ������� �ʾƾ� ���׹̳ʸ� ȸ������
	UPROPERTY(EditAnywhere, Category = "Info")
	float Heal_Stamina_Time;

	// �ʴ� ȸ���ϴ� ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Info")
	float Heal_Stamina_PerSec;
		
	// ��������
	UPROPERTY(EditAnywhere, Category = "Info")
	bool Invincible;

	// ���۾Ƹ� ��������
	UPROPERTY(EditAnywhere, Category = "Info")
	bool SuperArmor;

	// �ǰ� �ִϸ��̼�
	UPROPERTY(EditAnywhere, Category = "Info")
	class UAnimMontage* HitMontage;

	// �ǰ� ����
	UPROPERTY(EditAnywhere, Category = "Info")
	class USoundBase* HitSound;
};
