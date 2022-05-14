// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWRPG_API IDamageObject
{
	GENERATED_BODY()

public:
	class AEntity* Attacker;

	int32 DamageRatio;		// ������ ���� (100 = 1��)
	int32 ManaRatio;		// ȹ�渶�� ���� (100 = 1��)
	float KnockbackAmount;  // �ڷ� ��ġ�� ����
	TSubclassOf<UMatineeCameraShake> CameraClass;

	// ������ �ʱ�ȭ�ϰ� �ı�(����)�ð��� ����
	virtual void SetData(class AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass) = 0;
};
