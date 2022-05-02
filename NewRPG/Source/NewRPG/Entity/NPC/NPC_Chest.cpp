// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Chest.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"


ANPC_Chest::ANPC_Chest()
{
	NPCName = TEXT("장비 / 인벤토리");

	SMesh_Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMesh_Body"));
	SMesh_Top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMesh_Top"));

	SMesh_Body->SetupAttachment(RootComponent);
	SMesh_Top->SetupAttachment(SMesh_Body);
	WidgetComp->SetupAttachment(SMesh_Body);
}


void ANPC_Chest::Interact()
{
	Super::Interact();

	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ShowInventory();
	}
}