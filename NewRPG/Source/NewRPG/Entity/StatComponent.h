// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWRPG_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatComponent();

protected:
	virtual void BeginPlay() override;


private:
	// 공격력, 기본(시작) 공격력
	float Strength;
	float OriginStrength;

	// 최대 체력과 현재 체력, 기본(시작)체력
	float Health;
	float CurrHealth;
	float OriginHealth;

	// 최대 마나와 현재 마나
	float Mana;
	float CurrMana;

	// 최대 스테미너와 현재 스테미너
	float Stamina;
	float CurrStamina;

	// 시작 방어력과 현재 방어력 (100 = 100%)
	// - 시작 방어력은 방어력 감소등의 효과 발생시 원래 방어력으로 되돌리기 위해 사용됨
	float OriginDefence;
	float CurrDefence;

	// 시작 크리티컬 확률, 크리티컬 확률 (100 = 100%)
	float OriginCritChance;
	float CritChance;

	// 시작 공격속도와 현재 공격속도 (20 = 20%, 최대 40%)
	float OriginASpeed;
	float CurrASpeed;


public:
	// * 공격력 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetStrength() { return Strength; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetOriginStrength() { return OriginStrength; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetStrength(int32 NewStrength) { Strength = NewStrength; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddStrength(int32 Amount) { Strength += Amount; }


	// * 체력 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetHealth() { return CurrHealth; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetMaxHealth() { return Health; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetOriginHealth() { return OriginHealth; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetHealth(float NewHealth) { CurrHealth = FMath::Clamp<float>(NewHealth, 0.0f, Health); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddHealth(float Amount) { CurrHealth = FMath::Clamp<float>(CurrHealth + Amount, 0.0f, Health); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetMaxHealth(float NewMaxHealth) { Health = FMath::Clamp<float>(NewMaxHealth, 0.0f, NewMaxHealth); }


	// * 마나 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetMana() { return CurrMana; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetMaxMana() { return Mana; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetMana(float NewMana) { CurrMana = FMath::Clamp<float>(NewMana, 0.0f, Mana); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddMana(float Amount) { CurrMana = FMath::Clamp<float>(CurrMana + Amount, 0.0f, Mana); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetMaxMana(float NewMaxMana) { Mana = FMath::Clamp<float>(NewMaxMana, 0.0f, NewMaxMana); }


	// * 스테미나 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetStamina() { return CurrStamina; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetMaxStamina() { return Stamina; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetStamina(float NewStamina) { CurrStamina = FMath::Clamp<float>(NewStamina, 0.0f, Stamina); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddStamina(float Amount) { CurrStamina = FMath::Clamp<float>(CurrStamina + Amount, 0.0f, Stamina); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetMaxStamina(float NewMaxStamina) { Stamina = FMath::Clamp<float>(NewMaxStamina, 0.0f, NewMaxStamina); }


	// * 방어력 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetDefence() { return CurrDefence; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetOriginDefence() { return OriginDefence; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetDefence(float NewDefence) { CurrDefence = FMath::Clamp<float>(NewDefence, 0.0f, 100.f); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddDefence(float Amount) { CurrDefence = FMath::Clamp<float>(CurrDefence + Amount, 0.0f, 100.f); }


	// * 크리티컬 확률 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetCritChance() { return CritChance; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetOriginCritChance() { return OriginCritChance; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetCritChance(float NewCritChance) { CritChance = FMath::Clamp<float>(NewCritChance, 0.0f, 100.f); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddCritChance(float Amount) { CritChance = FMath::Clamp<float>(CritChance + Amount, 0.0f, 100.f); }


	// * 공격속도 Get / Set
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetASpeed() { return CurrASpeed; }

	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetOriginASpeed() { return OriginASpeed; }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetASpeed(float NewASpeed) { CurrASpeed = FMath::Clamp<float>(NewASpeed, 0.0f, 40.f); }

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddASpeed(float Amount) { CurrASpeed = FMath::Clamp<float>(CurrASpeed + Amount, 0.0f, 40.f); }


public:
	UFUNCTION(BlueprintCallable, Category = "Stat")
	void HealAll();
};
