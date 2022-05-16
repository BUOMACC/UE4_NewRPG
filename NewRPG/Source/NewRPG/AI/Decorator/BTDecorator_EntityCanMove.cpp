// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_EntityCanMove.h"
#include "AIController.h"
#include "Entity/Entity.h"


UBTDecorator_EntityCanMove::UBTDecorator_EntityCanMove()
{
	NodeName = TEXT("Entity CanMove?");
}


bool UBTDecorator_EntityCanMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEntity* Target = Cast<AEntity>(OwnerComp.GetAIOwner()->GetPawn());
	if (Target)
	{
		return Target->GetCanMove();
	}
	return true;
}