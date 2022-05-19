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

	// ���� ���ӽð� ����
	UFUNCTION()
	void UpdateBuffDuration();

	// ���� ��ġ ���
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
	FOnApplyBuff OnApplyBuff;	// ������ ������� ���
	FOnExpireBuff OnExpireBuff;	// ������ ���ӽð� �Ǵ� �ص����� ����� ���

	// ���� �߰�
	UFUNCTION(BlueprintCallable)
	void AddBuff(UBuffData* NewBuff);

	// ���� ����
	UFUNCTION(BlueprintCallable)
	void RemoveBuff(int32 BuffIndex);

	// ������ ������ ���� ��ġ
	UFUNCTION(BlueprintPure)
	float GetBuffAmount(EBuffType BuffType);
};
