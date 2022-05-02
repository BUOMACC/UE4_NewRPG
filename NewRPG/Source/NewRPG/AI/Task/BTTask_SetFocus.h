// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTTask_SetFocus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_SetFocus();

protected:
	UPROPERTY(EditAnywhere)
	bool bFocusPlayer;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
