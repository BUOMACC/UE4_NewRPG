// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class NEWRPG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

protected:
	class AEntity* ProjectileOwner;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DestroyEffect;

public:
	UFUNCTION(BlueprintCallable)
	void SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime);

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	int32 DamageRatio;		// ������ ���� (100 = 1��)
	int32 ManaRatio;		// ȹ�渶�� ���� (100 = 1��)
	float KnockbackAmount;  // �ڷ� ��ġ�� ����
};
