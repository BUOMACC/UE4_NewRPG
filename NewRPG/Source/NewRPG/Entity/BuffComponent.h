// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/BuffData.h"
#include "BuffComponent.generated.h"


DECLARE_DELEGATE_TwoParams(FOnApplyBuff, UBuffData*, bool);
DECLARE_DELEGATE_OneParam(FOnExpireBuff, UBuffData*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWRPG_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();

protected:
	virtual void BeginPlay() override;

	// 버프 지속시간 갱신
	UFUNCTION()
	void UpdateBuffDuration();

	// 버프 수치 계산
	UFUNCTION()
	void CalcBuffAmount(EBuffType BuffType, float Amount);

private:
	UPROPERTY()
	TArray<class UBuffData*> Buffs;
	
	UPROPERTY()
	TArray<int32> StartTime;

	float PowerUPAmount;
	float ArmorUPAmount;
	float SpeedAmount;
	float BleedingAmount;

public:
	FOnApplyBuff OnApplyBuff;	// 버프를 적용받은 경우
	FOnExpireBuff OnExpireBuff;	// 버프의 지속시간 또는 해독으로 종료된 경우

	// 버프 추가
	UFUNCTION(BlueprintCallable)
	void AddBuff(UBuffData* NewBuff);

	// 버프 제거
	UFUNCTION(BlueprintCallable)
	void RemoveBuff(int32 BuffIndex);

	// 선택한 버프의 총합 수치
	UFUNCTION(BlueprintPure)
	float GetBuffAmount(EBuffType BuffType);
};
