// Copyright Epic Games, Inc. All Rights Reserved.


#include "NewRPGGameModeBase.h"
#include "Pool/DamageText.h"

ANewRPGGameModeBase::ANewRPGGameModeBase()
{
	PoolCount = 50;
}


void ANewRPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (DamageTextClass == nullptr) return;

	for (int i = 0; i < PoolCount; i++)
	{
		ADamageText* PoolActor = GetWorld()->SpawnActor<ADamageText>(DamageTextClass, FVector::ZeroVector, FRotator::ZeroRotator);
		PoolActor->PoolRef = this;

		Pool.Enqueue(PoolActor);
	}
}


ADamageText* ANewRPGGameModeBase::SpawnDamageText(FVector SpawnLoc, float DamageAmount, bool bIsCritical)
{
	if (Pool.IsEmpty()) return nullptr;

	// 풀에서 데미지 텍스트 액터를 활성화 시키고 반환
	ADamageText* PoolActor;
	Pool.Dequeue(PoolActor);

	SpawnLoc.Y += FMath::RandRange(-70.f, 70.f);
	SpawnLoc.Z += FMath::RandRange(0.f, 70.f);

	PoolActor->SetDamageText(DamageAmount, bIsCritical);
	PoolActor->SetActorLocation(SpawnLoc);
	PoolActor->SetEnable(true);

	return PoolActor;
}