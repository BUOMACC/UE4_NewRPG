// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerLoc.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API UBTService_UpdatePlayerLoc : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_UpdatePlayerLoc();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
