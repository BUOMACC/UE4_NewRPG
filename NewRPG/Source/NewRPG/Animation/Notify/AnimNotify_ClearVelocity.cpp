// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_ClearVelocity.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimNotify_ClearVelocity::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Target = Cast<ACharacter>(MeshComp->GetOwner());
	if (Target)
	{
		Target->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	}
}


FString UAnimNotify_ClearVelocity::GetNotifyName_Implementation() const
{
	return TEXT("ClearVelocity");
}