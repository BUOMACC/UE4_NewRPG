// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomNumber.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_RandomNumber::UBTService_RandomNumber()
{
	NodeName = TEXT("Random Number");
}


void UBTService_RandomNumber::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FName SelectKey = GetSelectedBlackboardKey();
	int32 Result = FMath::RandRange(MinNum, MaxNum);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(SelectKey, Result);
}
