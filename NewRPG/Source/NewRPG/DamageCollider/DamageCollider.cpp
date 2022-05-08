// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageCollider.h"
#include "Entity/Entity.h"
#include "Kismet/GameplayStatics.h"


ADamageCollider::ADamageCollider()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageRatio = 0;
	ManaRatio = 0;
	KnockbackAmount = 0.f;
}


void ADamageCollider::SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MPRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass)
{
	ColliderOwner = WhoSpawned;
	DamageRatio = DmgRatio;
	ManaRatio = MPRatio;
	KnockbackAmount = Knockback;
	CameraClass = NewCameraClass;

	SetLifeSpan(LifeTime);
}


void ADamageCollider::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// DamageCollider의 주인이 있는 경우에만 호출
	if (ColliderOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, (float)ColliderOwner->CalculateDamage(DamageRatio), ColliderOwner->GetController(), this, UDamageType::StaticClass());
	}
}
