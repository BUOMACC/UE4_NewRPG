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

	int32 DamageRatio;		// 데미지 비율 (100 = 1배)
	int32 ManaRatio;		// 획득마나 비율 (100 = 1배)
	float KnockbackAmount;  // 뒤로 밀치는 강도
	TSubclassOf<UMatineeCameraShake> CameraClass;

	// 값들을 초기화하고 파괴(삭제)시간을 설정
	virtual void SetData(class AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass) = 0;
};
