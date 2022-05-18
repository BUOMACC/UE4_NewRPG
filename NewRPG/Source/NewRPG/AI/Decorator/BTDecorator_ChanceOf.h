// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_ChanceOf.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTDecorator_ChanceOf : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTDecorator_ChanceOf();

protected:
	UPROPERTY(EditAnywhere, Category = "Chance")
	int32 Chance;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
