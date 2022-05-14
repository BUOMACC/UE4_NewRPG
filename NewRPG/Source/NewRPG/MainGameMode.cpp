// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Data/DropData.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Pool/DamageText.h"
#include "UI/Game/DungeonClear.h"


AMainGameMode::AMainGameMode()
{
	EnemyCount = 0;
	PoolCount = 50;
}


void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 게임종료 위젯 생성
	if (DungeonEndClass)
	{
		DungeonEndWidget = CreateWidget<UDungeonClear>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DungeonEndClass);
	}

	// DamageText Pooling
	if (DamageTextClass == nullptr) return;

	for (int i = 0; i < PoolCount; i++)
	{
		ADamageText* PoolActor = GetWorld()->SpawnActor<ADamageText>(DamageTextClass, FVector::ZeroVector, FRotator::ZeroRotator);
		PoolActor->PoolRef = this;

		Pool.Enqueue(PoolActor);
	}
}


void AMainGameMode::AddEnemyCount(int32 Amount)
{
	EnemyCount += Amount;
	EnemyCount = FMath::Clamp(EnemyCount, 0, 999);

	// 모든 적이 죽었다면 클리어
	if (EnemyCount <= 0)
	{
		GameClear();
	}
}


ADamageText* AMainGameMode::SpawnDamageText(FVector SpawnLoc, float DamageAmount, bool bIsCritical)
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


void AMainGameMode::GameClear()
{
	if (DungeonEndWidget == nullptr || DungeonEndWidget->IsInViewport()) return;

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]()
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);
		DungeonEndWidget->AddToViewport();
		DungeonEndWidget->PlayEndAnimation(true);
		DungeonEndWidget->AddRewardsToInventory(DropData, DropCycle);
		DungeonEndWidget->AddGoldToInventory(FMath::RandRange(Min_Gold, Max_Gold));
	}), 3.f, false);
}


void AMainGameMode::GameOver()
{
	if (DungeonEndWidget == nullptr || DungeonEndWidget->IsInViewport()) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]()
	{
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);
		DungeonEndWidget->AddToViewport();
		DungeonEndWidget->PlayEndAnimation(false);
	}), 3.f, false);
}