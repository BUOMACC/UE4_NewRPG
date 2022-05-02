// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBox.h"
#include "Components/BoxComponent.h"


ADamageBox::ADamageBox()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageBox::OnBeginOverlap);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ADamageBox::SetBoxSize(FVector& BoxSize)
{
	BoxComponent->SetBoxExtent(BoxSize);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}