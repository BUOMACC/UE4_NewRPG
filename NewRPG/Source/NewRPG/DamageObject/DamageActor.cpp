// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "Entity/Entity.h"
#include "Data/BuffData.h"


void ADamageActor::SetData(AEntity* WhoSpawned, int32 NewDamageRatio, int32 NewManaRatio, float NewKnockbackAmount, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass, UBuffData* NewBuffData)
{
	Attacker = WhoSpawned;
	DamageRatio = NewDamageRatio;
	ManaRatio = NewManaRatio;
	KnockbackAmount = NewKnockbackAmount;
	CameraClass = NewCameraClass;
	BuffData = NewBuffData;

	SetLifeSpan(LifeTime);
}