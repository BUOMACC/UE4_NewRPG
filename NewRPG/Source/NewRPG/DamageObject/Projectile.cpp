// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/BuffData.h"
#include "Entity/Entity.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	RootComponent = BoxComponent;
	Mesh->SetupAttachment(RootComponent);
	ParticleSystem->SetupAttachment(RootComponent);
}


void AProjectile::SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass, UBuffData* NewBuffData)
{
	Attacker = WhoSpawned;
	DamageRatio = DmgRatio;
	ManaRatio = MpRatio;
	KnockbackAmount = Knockback;
	CameraClass = NewCameraClass;
	BuffData = NewBuffData;

	SetLifeSpan(LifeTime);
}


void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Attacker)
	{
		// 1) 닿은 액터가 Entity인 경우 피해를 입힘
		AEntity* Victim = Cast<AEntity>(OtherActor);
		if (Victim)
		{
			UGameplayStatics::ApplyDamage(OtherActor, (float)Attacker->CalculateDamage(DamageRatio), Attacker->GetController(), this, UDamageType::StaticClass());
		}

		// 2) 충돌시 이펙트 생성
		if (DestroyEffect == nullptr)
			return;
		FTransform SpawnTrans;
		SpawnTrans.SetLocation(GetActorLocation());
		SpawnTrans.SetRotation(FQuat::Identity);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, SpawnTrans, true, EPSCPoolMethod::None, true);

		// 3) 사운드 재생
		if (DestroySound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation());

		// 4) 자신은 파괴시킴
		Destroy();
	}
}