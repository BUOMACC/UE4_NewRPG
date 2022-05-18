// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_ChanceOf.h"


UBTDecorator_ChanceOf::UBTDecorator_ChanceOf()
{
	NodeName = TEXT("Chance Of N%");
}


bool UBTDecorator_ChanceOf::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	int32 RNum = FMath::RandRange(0, 99);
	if (RNum < Chance)
	{
		return true;
	}

	return false;
}