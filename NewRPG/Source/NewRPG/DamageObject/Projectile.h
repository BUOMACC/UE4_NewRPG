// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageObject.h"
#include "Projectile.generated.h"

UCLASS()
class NEWRPG_API AProjectile : public AActor, public IDamageObject
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
	virtual void SetData(AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass, class UBuffData* NewBuffData) override;
};
