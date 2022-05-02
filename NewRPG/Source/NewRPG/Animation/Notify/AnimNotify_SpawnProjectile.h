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
	float SpawnOffsetForward;	// 캐릭터를 기준으로 얼마나 앞에 스폰될지

	UPROPERTY(EditAnywhere)
	float SpawnOffsetRight;		// 캐릭터를 기준으로 얼마나 오른쪽에 스폰될지

	UPROPERTY(EditAnywhere)
	float SpawnUp;				// 캐릭터를 기준으로 얼마나 위에 스폰될지

	UPROPERTY(EditAnywhere)
	int32 DamageRatio;			// 데미지 비율 (100 = 1배)

	UPROPERTY(EditAnywhere)
	int32 ManaRatio;			// 획득마나 비율 (100 = 1배)

	UPROPERTY(EditAnywhere)
	float Knockback;			// 뒤로 밀치는 강도

	UPROPERTY(EditAnywhere)
	float LifeTime;				// Projectile 유지시간

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
