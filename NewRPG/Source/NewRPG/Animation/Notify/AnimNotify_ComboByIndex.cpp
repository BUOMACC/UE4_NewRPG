// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboByIndex.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "Entity/Entity.h"


void UAnimNotify_ComboByIndex::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AEntity* Target = Cast<AEntity>(MeshComp->GetOwner());
	if (Target)
	{
		UAttackComponent* AttackComp = Target->GetAttackComponent();
		if (AttackComp)
		{
			AttackComp->PlayComboAnimByIndex(ComboIndex, 1.f + (Target->GetStatComponent()->GetASpeed() / 100.f));
		}
	}
}


FString UAnimNotify_ComboByIndex::GetNotifyName_Implementation() const
{
	return TEXT("ComboByIndex");
}
