// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayMontage.h"
#include "AIController.h"
#include "Entity/AttackComponent.h"
#include "Entity/Entity.h"


UBTTask_PlayMontage::UBTTask_PlayMontage()
{
	PlayRate = 1.f;

	NodeName = TEXT("PlayMontage");
}


EBTNodeResult::Type UBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEntity* Target = Cast<AEntity>(OwnerComp.GetAIOwner()->GetPawn());
	if (Target && AnimMT)
	{
		Target->PlayAnimMontage(AnimMT, PlayRate);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}