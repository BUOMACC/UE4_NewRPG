// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PlayComboByIndex.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTTask_PlayComboByIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_PlayComboByIndex();

protected:
	// 실행할 콤보의 Index (ComboData를 기반으로 동작)
	UPROPERTY(EditAnywhere)
	int32 ComboIndex;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
