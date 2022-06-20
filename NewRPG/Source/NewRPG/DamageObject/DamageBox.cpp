// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBox.h"
#include "Components/BoxComponent.h"
#include "Data/BuffData.h"
#include "Entity/Entity.h"
#include "Kismet/GameplayStatics.h"


ADamageBox::ADamageBox()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageBox::OnBeginOverlap);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ADamageBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// DamageCollider�� ������ �ִ� ��쿡�� ȣ��
	if (Attacker)
	{
		UGameplayStatics::ApplyDamage(OtherActor, (float)Attacker->CalculateDamage(DamageRatio), Attacker->GetController(), this, UDamageType::StaticClass());
	}
}



void ADamageBox::SetBoxSize(FVector& BoxSize)
{
	BoxComponent->SetBoxExtent(BoxSize);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}