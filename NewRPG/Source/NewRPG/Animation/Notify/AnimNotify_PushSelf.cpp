// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PushSelf.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimNotify_PushSelf::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Target = Cast<ACharacter>(MeshComp->GetOwner());
	if (Target)
	{
		FVector PushDirForward = Target->GetActorForwardVector() * PushPower_Forward;
		FVector PushDirUp = Target->GetActorUpVector() * PushPower_Up;
		Target->GetCharacterMovement()->Launch(PushDirForward + PushDirUp);
	}
}


FString UAnimNotify_PushSelf::GetNotifyName_Implementation() const
{
	return TEXT("Push Self");
}