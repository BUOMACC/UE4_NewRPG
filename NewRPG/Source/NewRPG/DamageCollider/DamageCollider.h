// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageCollider.generated.h"

UCLASS()
class NEWRPG_API ADamageCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageCollider();

public:
	class AEntity* ColliderOwner;

	int32 DamageRatio;		// ������ ���� (100 = 1��)
	int32 ManaRatio;		// ȹ�渶�� ���� (100 = 1��)
	float KnockbackAmount;  // �ڷ� ��ġ�� ����
	TSubclassOf<UMatineeCameraShake> CameraClass;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass);

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
