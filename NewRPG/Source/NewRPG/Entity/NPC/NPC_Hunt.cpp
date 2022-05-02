// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Hunt.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"


ANPC_Hunt::ANPC_Hunt()
{
	NPCName = TEXT("몬스터 토벌");
}


void ANPC_Hunt::Interact()
{
	Super::Interact();

	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenDungeonMenu();
	}
}