// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_TeleportToPlayer.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"


void UAnimNotify_TeleportToPlayer::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* Mover = MeshComp->GetOwner();
	ACharacter* Target = UGameplayStatics::GetPlayerCharacter(Mover->GetWorld(), 0);

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(Mover->GetWorld());
	if (NavSys && Mover && Target)
	{
		FNavLocation TPPoint;
		NavSys->GetRandomPointInNavigableRadius(Target->GetActorLocation(), Radius, TPPoint);
		Mover->SetActorLocation(TPPoint.Location + FVector(0.f, 0.f, 100.f));
	}
}


FString UAnimNotify_TeleportToPlayer::GetNotifyName_Implementation() const
{
	return TEXT("Teleport_to_Player");
}
