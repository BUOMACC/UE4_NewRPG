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
		// 1) �ӵ� ��� - �̵� �ִϸ��̼�
		FVector Velocity = Target->GetMovementComponent()->Velocity;
		Speed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

		// 2) �������� �ִ������� üũ - ���� �ִϸ��̼�
		bIsFalling = Target->GetMovementComponent()->IsFalling();

		// 3) �׾����� üũ
		bIsDead = Target->GetIsDead();
	}
}