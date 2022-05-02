// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/CharacterAnimInstance.h"
#include "Entity/Player/BasePlayer.h"


void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasePlayer* Target = Cast<ABasePlayer>(TryGetPawnOwner());
	if (Target)
	{
		// 1) 공격모드인지 체크
		bBattleMode = Target->GetBattleMode();
	}
}