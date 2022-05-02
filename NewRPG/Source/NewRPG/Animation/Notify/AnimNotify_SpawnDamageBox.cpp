// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnDamageBox.h"
#include "DamageCollider/DamageBox.h"
#include "Entity/Entity.h"


FString UAnimNotify_SpawnDamageBox::GetNotifyName_Implementation() const
{
	return TEXT("SpawnDamageBox");
}


void UAnimNotify_SpawnDamageBox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AEntity* Owner = Cast<AEntity>(MeshComp->GetOwner());
	if (Owner && DamageBoxClass)
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

			ADamageBox* DamageBox = World->SpawnActor<ADamageBox>(DamageBoxClass, SpawnLoc, SpawnRot);
			DamageBox->SetData(Owner, DamageRatio, ManaRatio, Knockback, LifeTime);
			DamageBox->SetBoxSize(BoxSize);
		}
	}
}
