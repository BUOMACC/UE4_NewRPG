// Fill out your copyright notice in the Description page of Project Settings.


#include "Pool/DamageText.h"
#include "Components/WidgetComponent.h"
#include "UI/Game/DamageTextWidget.h"
#include "MainGameMode.h"


ADamageText::ADamageText()
{
	PrimaryActorTick.bCanEverTick = true;

	// * 데미지 표시를 위한 WidgetComponent 생성
	DTWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageTextWidget"));
	RootComponent = DTWidgetComponent;
	DTWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	VisibleTime = 3.0f;
}


void ADamageText::BeginPlay()
{
	Super::BeginPlay();

	DTWidgetComponent->SetHiddenInGame(true);
}


void ADamageText::EnqueuePool()
{
	if (PoolRef)
	{
		PoolRef->Pool.Enqueue(this);
		DTWidgetComponent->SetHiddenInGame(true);
	}
	else
	{
		Destroy();
	}
}


void ADamageText::SetEnable(bool Flag)
{
	if (Flag == true)
	{
		DTWidgetComponent->SetHiddenInGame(false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADamageText::EnqueuePool, VisibleTime, false);
	}
	else
	{
		EnqueuePool();
	}
}


void ADamageText::SetDamageText(float DamageAmount, bool bIsCritical)
{
	if (DTWidgetComponent->GetUserWidgetObject() == nullptr) return;

	UDamageTextWidget* DTWidget = Cast<UDamageTextWidget>(DTWidgetComponent->GetUserWidgetObject());
	if (DTWidget)
	{
		DTWidget->SetDamageText(DamageAmount, bIsCritical);
	}
}