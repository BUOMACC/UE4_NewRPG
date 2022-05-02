// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayComboByIndex.h"
#include "AIController.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "Entity/Entity.h"


UBTTask_PlayComboByIndex::UBTTask_PlayComboByIndex()
{
	ComboIndex = 0;

	NodeName = TEXT("PlayComboByIndex");
}


EBTNodeResult::Type UBTTask_PlayComboByIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEntity* Target = Cast<AEntity>(OwnerComp.GetAIOwner()->GetPawn());
	if (Target)
	{
		UAttackComponent* AttackComp = Target->GetAttackComponent();
		if (AttackComp)
		{
			AttackComp->PlayComboAnimByIndex(ComboIndex, 1.f + (Target->GetStatComponent()->GetASpeed() / 100.f));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
