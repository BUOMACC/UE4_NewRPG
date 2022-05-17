// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/BuffData.h"
#include "Entity.generated.h"

UCLASS()
class NEWRPG_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// DataTable을 통해 구분할때 또는 UI에 이름을 표시할때 사용함
	UPROPERTY(EditAnywhere, Category = "Entity Data")
	FText EntityName;

protected:
	float OriginSpd;	// 저장용 기본 이동속도
	float MoveSpd;		// 기본 이동속도

	bool bInvincible;
	bool bSuperArmor;
	bool bCanMove;
	bool bIsDead;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(AEntity* Victim, float Damage, TSubclassOf<UMatineeCameraShake> CameraClass);
	virtual void Dead(AActor* Killer);

	UFUNCTION()
	void OnApplyBuff(class UBuffData* Buff, bool AlreadyHasBuff);

	UFUNCTION()
	void OnExpireBuff(class UBuffData* Buff);

	UFUNCTION()
	void WaitToStart();

protected:
	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComp;

	UPROPERTY(VisibleAnywhere)
	class UAttackComponent* AttackComp;

	UPROPERTY(VisibleAnywhere)
	class UBuffComponent* BuffComp;

	UPROPERTY()
	class USoundBase* HitSound;

	UPROPERTY()
	class UAnimMontage* HitMontage;

public:
	UFUNCTION(BlueprintPure, Category = "Entity")
	UStatComponent* GetStatComponent() { return StatComp; }

	UFUNCTION(BlueprintPure, Category = "Entity")
	UAttackComponent* GetAttackComponent() { return AttackComp; }

	UFUNCTION(BlueprintPure, Category = "Entity")
	UBuffComponent* GetBuffComponent() { return BuffComp; }

	UFUNCTION(BlueprintCallable, Category = "Entity")
	void SetSuperArmor(bool Flag) { bSuperArmor = Flag; }

	UFUNCTION(BlueprintPure, Category = "Entity")
	bool GetIsDead() { return bIsDead; }

	UFUNCTION(BlueprintPure, Category = "Entity")
	bool GetCanMove() { return bCanMove; }

	UFUNCTION(BlueprintPure, Category = "Entity")
	float CalculateDamage(float RatioAmount);		// RatioAmount : 100 = 기본 Strength가 데미지

	UFUNCTION(BlueprintPure, Category = "Entity")
	bool CalculateCritical();

};
