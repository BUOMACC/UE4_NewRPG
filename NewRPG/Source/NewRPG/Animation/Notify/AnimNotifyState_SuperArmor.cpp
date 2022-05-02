// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_SuperArmor.h"
#include "Entity/Entity.h"


FString UAnimNotifyState_SuperArmor::GetNotifyName_Implementation() const
{
	return TEXT("SuperArmor");
}


void UAnimNotifyState_SuperArmor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AEntity* Target = Cast<AEntity>(MeshComp->GetOwner());
	if (Target)
	{
		Target->SetSuperArmor(true);
	}
}


void UAnimNotifyState_SuperArmor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AEntity* Target = Cast<AEntity>(MeshComp->GetOwner());
	if (Target)
	{
		Target->SetSuperArmor(false);
	}
}