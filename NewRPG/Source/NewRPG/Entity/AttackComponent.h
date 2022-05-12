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
	// ���� �޺� �ε���
	int ComboIndex;
	// �޺��� ������ Ÿ�̹����� (true�̸� ������ ���� & �޺� ���� ����)
	bool bComboTiming;
	// ���� ��������
	bool bIsAttack;

	// ó�� ���ʰ��ݽ� ����Ǵ� ���� �ε���
	UPROPERTY(EditAnywhere, Category = "Attack")
	int DefaultComboIndexL;
	// ó�� �����ʰ��ݽ� ����Ǵ� ���� �ε���
	UPROPERTY(EditAnywhere, Category = "Attack")
	int DefaultComboIndexR;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UComboData* ComboData;

public:
	// AttackData���� ������ ������ �����մϴ�.
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRandom(float PlaySpeed);

	// AttackData���� ���ʿ� �ش��ϴ� ������ �����մϴ�. (�޺��� �̾����� �ֽ��ϴ�)
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackLeft(float PlaySpeed);

	// AttackData���� �����ʿ� �ش��ϴ� ������ �����մϴ�. (�޺��� �̾����� �ֽ��ϴ�)
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRight(float PlaySpeed);

	// ������ ����մϴ�.
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CancelAttack();

	// bComboTiming ���� ���� ���� ���� ������ �޺��� ����մϴ�. ���Ϳ� ���˴ϴ�
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
