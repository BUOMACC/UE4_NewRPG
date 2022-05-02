// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetFlyMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimNotify_SetFlyMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Target = Cast<ACharacter>(MeshComp->GetOwner());
	if (Target)
	{
		if (EnableFlyMode)
		{
			Target->GetCharacterMovement()->GravityScale = 0.f;
		}
		else
		{
			Target->GetCharacterMovement()->GravityScale = 1.f;
		}
	}
}


FString UAnimNotify_SetFlyMode::GetNotifyName_Implementation() const
{
	return TEXT("SetFlyMode");
}