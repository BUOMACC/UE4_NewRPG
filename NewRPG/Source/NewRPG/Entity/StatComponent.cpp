// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"


UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Strength = 50.f;
	OriginStrength = 50.f;

	Health = 100.f;
	CurrHealth = 0.f;
	OriginHealth = 100.f;

	Mana = 100.f;
	CurrMana = 0.f;

	Stamina = 100.f;
	CurrStamina = 0.f;

	OriginDefence = 0.f;
	CurrDefence = 0.f;

	CritChance = 0.f;

	OriginASpeed = 0.f;
	CurrASpeed = 0.f;
}


void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	HealAll();
}


void UStatComponent::HealAll()
{
	// 모두 회복
	CurrHealth = Health;
	CurrMana = Mana;
	CurrStamina = Stamina;
}


void UStatComponent::InitOriginStat()
{
	// 기본값 설정
	OriginHealth = CurrHealth;
	OriginStrength = Strength;
	OriginDefence = CurrDefence;
	OriginCritChance = CritChance;
	OriginASpeed = CurrASpeed;
}