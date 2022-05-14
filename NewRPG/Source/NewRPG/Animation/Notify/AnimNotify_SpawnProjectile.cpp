// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnProjectile.h"
#include "Entity/Entity.h"
#include "DamageObject/Projectile.h"


FString UAnimNotify_SpawnProjectile::GetNotifyName_Implementation() const
{
	return TEXT("SpawnProjectile");
}


void UAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AEntity* Owner = Cast<AEntity>(MeshComp->GetOwner());
	if (Owner && ProjectileClass)
	{
		UWorld* World = Owner->GetWorld();

		if (World)
		{
			// Spawn Collider
			FVector ForwardVec = Owner->GetActorForwardVector() * SpawnOffsetForward;
			FVector RightVec = Owner->GetActorRightVector() * SpawnOffsetRight;
			FVector UpVec = Owner->GetActorUpVector() * SpawnUp;
			FVector SpawnLoc = Owner->GetActorLocation() + (ForwardVec + RightVec + UpVec);

			FRotator SpawnRot = Owner->GetActorRotation();

			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
			Projectile->SetData(Owner, DamageRatio, ManaRatio, Knockback, LifeTime, CameraClass);
		}
	}
}
