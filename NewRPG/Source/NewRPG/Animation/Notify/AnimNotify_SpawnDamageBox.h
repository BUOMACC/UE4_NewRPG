// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnDamageBox.generated.h"

/**
 * 데미지를 주는 콜라이더를 생성하는 Notify
 */
UCLASS(meta = (DisplayName = "SpawnDamageBox"))
class NEWRPG_API UAnimNotify_SpawnDamageBox : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADamageBox> DamageBoxClass;

	UPROPERTY(EditAnywhere)
	FVector BoxSize;		// 크기

	UPROPERTY(EditAnywhere)
	float SpawnOffsetForward;		// 캐릭터를 기준으로 얼마나 앞에 스폰될지

	UPROPERTY(EditAnywhere)
	float SpawnOffsetRight;			// 캐릭터를 기준으로 얼마나 오른쪽에 스폰될지

	UPROPERTY(EditAnywhere)
	float SpawnUp;			// 캐릭터를 기준으로 얼마나 위에 스폰될지

	UPROPERTY(EditAnywhere)
	int32 DamageRatio;		// 데미지 비율 (100 = 1배)

	UPROPERTY(EditAnywhere)
	int32 ManaRatio;		// 획득마나 비율 (100 = 1배)
	
	UPROPERTY(EditAnywhere)
	float Knockback;		// 뒤로 밀치는 강도

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> CameraClass;	// 카메라 흔들림

	UPROPERTY(EditAnywhere)
	class UBuffData* BuffData;	// 적용할 디버프

	UPROPERTY(EditAnywhere)
	float LifeTime;				// Collider 유지시간

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
