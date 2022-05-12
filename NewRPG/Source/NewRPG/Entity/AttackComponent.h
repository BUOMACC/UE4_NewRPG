// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Struct/ComboElement.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWRPG_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class AEntity* OwnerComp;

protected:
	// 현재 콤보 인덱스
	int ComboIndex;
	// 콤보가 가능한 타이밍인지 (true이면 공격이 가능 & 콤보 연계 가능)
	bool bComboTiming;
	// 공격 상태인지
	bool bIsAttack;

	// 처음 왼쪽공격시 실행되는 공격 인덱스
	UPROPERTY(EditAnywhere, Category = "Attack")
	int DefaultComboIndexL;
	// 처음 오른쪽공격시 실행되는 공격 인덱스
	UPROPERTY(EditAnywhere, Category = "Attack")
	int DefaultComboIndexR;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UComboData* ComboData;

public:
	// AttackData에서 랜덤한 공격을 실행합니다.
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRandom(float PlaySpeed);

	// AttackData에서 왼쪽에 해당하는 공격을 실행합니다. (콤보가 이어질수 있습니다)
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackLeft(float PlaySpeed);

	// AttackData에서 오른쪽에 해당하는 공격을 실행합니다. (콤보가 이어질수 있습니다)
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRight(float PlaySpeed);

	// 공격을 취소합니다.
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CancelAttack();

	// bComboTiming 같은 변수 제약 없이 무조건 콤보를 재생합니다. 몬스터에 사용됩니다
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void PlayComboAnimByIndex(int32 Index, float PlaySpeed);

	UFUNCTION(BlueprintPure, Category = "Attack")
	int32 GetComboIndex() { return ComboIndex; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetComboIndex(int32 ComboIdx) { ComboIndex = ComboIdx; }

	UFUNCTION(BlueprintPure, Category = "Attack")
	bool GetComboTiming() { return bComboTiming; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetComboTiming(bool ComboTiming) { bComboTiming = ComboTiming; }

	UFUNCTION(BlueprintPure, Category = "Attack")
	bool GetIsAttack() { return bIsAttack; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetIsAttack(bool IsAttack) { bIsAttack = IsAttack; }

	UFUNCTION(BlueprintPure, Category = "Attack")
	float GetNextLeftComboCost();

	UFUNCTION(BlueprintPure, Category = "Attack")
	float GetNextRightComboCost();
};
