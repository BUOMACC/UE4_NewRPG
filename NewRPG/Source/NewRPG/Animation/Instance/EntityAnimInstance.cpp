// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Entity/Entity.h"


void UEntityAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEntity* Target = Cast<AEntity>(TryGetPawnOwner());
	if (Target)
	{
		// 1) 속도 계산 - 이동 애니메이션
		FVector Velocity = Target->GetMovementComponent()->Velocity;
		Speed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

		// 2) 떨어지고 있는중인지 체크 - 공중 애니메이션
		bIsFalling = Target->GetMovementComponent()->IsFalling();

		// 3) 죽었는지 체크
		bIsDead = Target->GetIsDead();
	}
}