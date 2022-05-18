// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateNearLoc.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTService_UpdateNearLoc : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateNearLoc();

protected:
	UPROPERTY(EditAnywhere)
	float Radius;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
