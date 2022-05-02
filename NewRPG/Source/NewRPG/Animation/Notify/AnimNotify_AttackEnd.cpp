// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackEnd.h"
#include "Entity/Entity.h"
#include "Entity/AttackComponent.h"


void UAnimNotify_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AEntity* Target = Cast<AEntity>(MeshComp->GetOwner());
	if (Target)
	{
		Target->GetAttackComponent()->CancelAttack();
	}
}


FString UAnimNotify_AttackEnd::GetNotifyName_Implementation() const
{
	return TEXT("AttackEnd");
}
