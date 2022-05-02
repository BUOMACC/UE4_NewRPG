// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetFocus.h"
#include "AI/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"


UBTTask_SetFocus::UBTTask_SetFocus()
{
	NodeName = TEXT("StartFocus");

	bFocusPlayer = false;
}


EBTNodeResult::Type UBTTask_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyAIController* AC = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (AC)
	{
		AC->SetFocusPlayer(bFocusPlayer);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}