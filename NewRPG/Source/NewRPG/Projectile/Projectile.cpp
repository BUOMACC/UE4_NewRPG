// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
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


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AProjectile::SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime)
{
	ProjectileOwner = WhoSpawned;
	DamageRatio = DmgRatio;
	ManaRatio = MpRatio;
	KnockbackAmount = Knockback;

	SetLifeSpan(LifeTime);
}


void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ProjectileOwner)
	{
		// 1) ���� ���Ͱ� Entity�� ��� ���ظ� ����
		AEntity* Victim = Cast<AEntity>(OtherActor);
		if (Victim)
		{
			UGameplayStatics::ApplyDamage(OtherActor, (float)ProjectileOwner->CalculateDamage(DamageRatio), ProjectileOwner->GetController(), this, UDamageType::StaticClass());
		}

		// 2) �浹�� ����Ʈ ����
		if (DestroyEffect == nullptr) return;
		FTransform SpawnTrans;
		SpawnTrans.SetLocation(GetActorLocation());
		SpawnTrans.SetRotation(FQuat::Identity);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, SpawnTrans, true, EPSCPoolMethod::None, true);

		// 3) �ڽ��� �ı���Ŵ
		Destroy();
	}
}