// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

class AEntity;
class UBuffData;

UCLASS()
class NEWRPG_API ADamageActor : public AActor
{
	GENERATED_BODY()

public:
	void SetData(AEntity* WhoSpawned, int32 NewDamageRatio, int32 NewManaRatio, float NewKnockbackAmount, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass, UBuffData* NewBuffData);

	// Getter
	UFUNCTION(BlueprintPure)
	AEntity* GetAttacker() { return Attacker; }

	UFUNCTION(BlueprintPure)
	int32 GetDamageRatio() { return DamageRatio; }

	UFUNCTION(BlueprintPure)
	int32 GetManaRatio() { return ManaRatio; }

	UFUNCTION(BlueprintPure)
	float GetKnockbackAmount() { return KnockbackAmount; }

	UFUNCTION(BlueprintPure)
	TSubclassOf<UMatineeCameraShake> GetCameraShakeClass() { return CameraClass; }

	UFUNCTION(BlueprintPure)
	UBuffData* GetBuffData() { return BuffData; }

protected:
	UPROPERTY()
	AEntity* Attacker;

	int32 DamageRatio;		// 데미지 비율 (100 = 1배)
	int32 ManaRatio;		// 획득마나 비율 (100 = 1배)
	float KnockbackAmount;  // 뒤로 밀치는 강도
	TSubclassOf<UMatineeCameraShake> CameraClass;

	UPROPERTY()
	UBuffData* BuffData;
};
