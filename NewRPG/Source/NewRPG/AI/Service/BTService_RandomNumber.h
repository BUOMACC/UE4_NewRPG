// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RandomNumber.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTService_RandomNumber : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_RandomNumber();

protected:
	// MinNum <= Result <= MaxNum

	UPROPERTY(EditAnywhere)
	int32 MinNum;
	
	UPROPERTY(EditAnywhere)
	int32 MaxNum;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
