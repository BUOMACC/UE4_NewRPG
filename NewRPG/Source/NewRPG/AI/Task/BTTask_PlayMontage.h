// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTTask_PlayMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_PlayMontage();

protected:
	// 재생할 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMT;

	// 재생시간
	UPROPERTY(EditAnywhere)
	float PlayRate;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
