// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLoc.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UBTService_UpdatePlayerLoc::UBTService_UpdatePlayerLoc()
{
	NodeName = TEXT("Update PlayerLoc");
}


void UBTService_UpdatePlayerLoc::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* Target = UGameplayStatics::GetPlayerCharacter(OwnerComp.GetWorld(), 0);
	if (Target)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Target->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}