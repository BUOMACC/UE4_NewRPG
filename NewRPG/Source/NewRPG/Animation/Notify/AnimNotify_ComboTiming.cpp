// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboTiming.h"
#include "Entity/Entity.h"
#include "Entity/AttackComponent.h"


void UAnimNotify_ComboTiming::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AEntity* Target = Cast<AEntity>(MeshComp->GetOwner());
	if (Target)
	{
		Target->GetAttackComponent()->SetComboTiming(bComboTiming);
	}
}


FString UAnimNotify_ComboTiming::GetNotifyName_Implementation() const
{
	return TEXT("ComboTiming");
}