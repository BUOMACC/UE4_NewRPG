// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMainGameMode();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UDungeonClear> DungeonEndClass;

	UPROPERTY()
	class UDungeonClear* DungeonEndWidget;

	// 클리어 보상
	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	class UDropData* DropData;

	// 클리어 보상이 몇번 지급될지
	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 DropCycle;

	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 Min_Gold;

	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 Max_Gold;

	// 적 객체수가 몇인지
	int32 EnemyCount;

public:
	// 게임 시작까지 얼마나 기다릴지/이동이 불가한지 - 컷씬에 주로 사용)
	UPROPERTY(EditAnywhere, Category = "CutScene")
	float WaitTime;

	void AddEnemyCount(int32 Amount);
	void GameClear();
	void GameOver();

// * DamageText Pooling
protected:
	UPROPERTY(EditAnywhere, Category = "Pool")
	TSubclassOf<class ADamageText> DamageTextClass;

	UPROPERTY(EditAnywhere, Category = "Pool")
	int32 PoolCount;

public:
	TQueue<class ADamageText*> Pool;

public:
	UFUNCTION(BlueprintCallable)
	ADamageText* SpawnDamageText(FVector SpawnLoc, float DamageAmount, bool bIsCritical);
};
