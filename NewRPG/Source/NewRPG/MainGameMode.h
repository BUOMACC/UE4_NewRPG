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

	int32 EnemyCount;

	// Ŭ���� ����
	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	class UDropData* DropData;

	// Ŭ���� ������ ��� ���޵���
	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 DropCycle;

	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 Min_Gold;

	UPROPERTY(EditAnywhere, Category = "Clear Reward")
	int32 Max_Gold;

public:
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
