// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	AEnemyAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY(EditAnywhere)
	bool bFocusPlayer;

public:
	UFUNCTION(BlueprintCallable)
	void SetFocusPlayer(bool Flag) { bFocusPlayer = Flag; }

protected:
	void CalcPlayerDistance();	// 플레이어와의 거리를 계산한뒤 Blackboard로 넘김 (PlayerDistance)
	void FocusPlayer();			// bFocusPlayer이 true인 동안 플레이어를 바라봄
};
