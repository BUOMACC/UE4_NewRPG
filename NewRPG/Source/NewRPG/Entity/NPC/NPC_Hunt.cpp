﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Hunt.h"
#include "Controller/PlayerGameController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Game/NameTag.h"


ANPC_Hunt::ANPC_Hunt()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName("NPC");

	// * WidgetComp 설정
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetupAttachment(GetMesh());
	WidgetComp->SetRelativeLocation(FVector(0, 0, 220.0f));
	WidgetComp->SetDrawSize(FVector2D(100.f, 10.f));

	// * 기본 Mesh 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ANPC_Hunt::BeginPlay()
{
	Super::BeginPlay();

	// Set NameTag
	UNameTag* NameTag = Cast<UNameTag>(WidgetComp->GetUserWidgetObject());
	if (NameTag)
	{
		NameTag->SetNameTag(NPCName);
	}
}


void ANPC_Hunt::Interact()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenDungeonMenu();
	}
}