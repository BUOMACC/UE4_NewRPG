// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	bFocusPlayer = false;
}


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);

		APawn* Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Target);
	}
}


void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalcPlayerDistance();
	FocusPlayer();
}


void AEnemyAIController::CalcPlayerDistance()
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player)
	{
		float Dist = FVector::Distance(Player->GetActorLocation(), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsFloat(TEXT("PlayerDistance"), Dist);
	}
}


void AEnemyAIController::FocusPlayer()
{
	if (!bFocusPlayer) return;

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player)
	{
		FVector StartLoc = GetPawn()->GetActorLocation();
		FVector PlayerLoc = Player->GetActorLocation();

		FRotator AIRot = GetPawn()->GetActorRotation();
		FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(StartLoc, PlayerLoc);

		FRotator TargetRot = FMath::Lerp(AIRot, LookRot, 0.15f);
		GetPawn()->SetActorRotation(FRotator(AIRot.Pitch, TargetRot.Yaw, AIRot.Roll));
	}
}
