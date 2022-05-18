// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateNearLoc.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Entity/Entity.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"


UBTService_UpdateNearLoc::UBTService_UpdateNearLoc()
{
	NodeName = TEXT("Random Near Location");
}


void UBTService_UpdateNearLoc::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEntity* OwnerEntity = Cast<AEntity>(OwnerComp.GetAIOwner()->GetPawn());
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (OwnerEntity && NavSys)
	{
		FNavLocation TPPoint;
		NavSys->GetRandomPointInNavigableRadius(OwnerEntity->GetActorLocation(), Radius, TPPoint);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TPPoint.Location);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}