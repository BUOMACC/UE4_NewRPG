// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Entity.h"
#include "Struct/ItemStat.h"
#include "BasePlayer.generated.h"

UCLASS()
class NEWRPG_API ABasePlayer : public AEntity
{
	GENERATED_BODY()

public:
	ABasePlayer();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> TestShake;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// ĳ������ ������ ����ִ� Table
	UPROPERTY(EditAnywhere, Category = "Character Data")
	class UDataTable* CharacterTable;


protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;


public:
	// ���ݸ�� �������� ������
	UFUNCTION(BlueprintPure, Category = "Character State")
	bool GetBattleMode() const { return bBattleMode; }

	// ���ݸ�� ����
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetBattleMode(bool BattleMode) { bBattleMode = BattleMode; }

	// ���ݸ�带 Toggle�� ����
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void ToggleBattleMode();

	// ī�޶� Shake
	UFUNCTION(BlueprintCallable, Category = "Character")
	void ShakeCamera(TSubclassOf<UMatineeCameraShake> ShakeData);

	// �߰� ��������
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SettingExtraStat();

protected:
	virtual void OnHit(AEntity* Victim, float Damage) override;


private:
	// �̵�
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void TurnRight(float Axis);
	void LookUp(float Axis);

	void RollingStart();
	void RollingEnd();
	void RollingMove();

	void AttackLeft();
	void AttackRight();

	void TryInteract();
	void Interact();

	// Character Table�κ��� ���� ������ ������� ������ ������
	void SettingStatFromTable();


private:
	// ���ݸ�忡�� �̵��ӵ�
	float BattleMoveSpd;

	// ������ �ӵ�, ������ �̵��ӵ�, ������ ���ӽð�, �Ҹ� ���׹̳�
	float RollingSpeed;
	float RollingMoveSpeed;
	float RollingTime;
	float RollingDecStamina;

	// ������ �ӽ� ����
	FVector RollingDirForward;
	FVector RollingDirRight;
	FVector RollingDir;

	// �⺻��� or ���ݸ�� ���� (false = �⺻���)
	bool bBattleMode;
	// ������ ������
	bool bRolling;

	// ���ݸ�� -> �⺻���� ��ȯ�Ҷ� ����Ǵ� �ִϸ��̼�
	class UAnimMontage* TravelStartMontage;

	// ������(ȸ��) �ִϸ��̼�
	class UAnimMontage* RollingMontage;

	// ��ȣ�ۿ� ����
	AActor* InteractActor;
};
