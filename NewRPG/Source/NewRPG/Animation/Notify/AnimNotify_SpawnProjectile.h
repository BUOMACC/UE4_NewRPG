// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnProjectile.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "SpawnProjectile"))
class NEWRPG_API UAnimNotify_SpawnProjectile : public UAnimNotify
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	float SpawnOffsetForward;	// ĳ���͸� �������� �󸶳� �տ� ��������

	UPROPERTY(EditAnywhere)
	float SpawnOffsetRight;		// ĳ���͸� �������� �󸶳� �����ʿ� ��������

	UPROPERTY(EditAnywhere)
	float SpawnUp;				// ĳ���͸� �������� �󸶳� ���� ��������

	UPROPERTY(EditAnywhere)
	int32 DamageRatio;			// ������ ���� (100 = 1��)

	UPROPERTY(EditAnywhere)
	int32 ManaRatio;			// ȹ�渶�� ���� (100 = 1��)

	UPROPERTY(EditAnywhere)
	float Knockback;			// �ڷ� ��ġ�� ����

	UPROPERTY(EditAnywhere)
	float LifeTime;				// Projectile �����ð�

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
