// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Chest.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Controller/PlayerGameController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Game/NameTag.h"


ANPC_Chest::ANPC_Chest()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetCollisionProfileName("NPC");
	RootComponent = BoxComp;

	// * SMesh_Body 설정
	SMesh_Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMesh_Body"));
	SMesh_Body->SetupAttachment(RootComponent);

	// * SMesh_Top 설정
	SMesh_Top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMesh_Top"));
	SMesh_Top->SetupAttachment(SMesh_Body);

	// * WidgetComp 설정
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetupAttachment(SMesh_Body);
	WidgetComp->SetRelativeLocation(FVector(0, 0, 220.0f));
	WidgetComp->SetDrawSize(FVector2D(100.f, 10.f));

	// * 기본 Mesh 설정
	SMesh_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SMesh_Top->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ANPC_Chest::BeginPlay()
{
	Super::BeginPlay();

	// Set NameTag
	UNameTag* NameTag = Cast<UNameTag>(WidgetComp->GetUserWidgetObject());
	if (NameTag)
	{
		NameTag->SetNameTag(NPCName);
	}
}


void ANPC_Chest::Interact()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ShowInventory();
	}
}