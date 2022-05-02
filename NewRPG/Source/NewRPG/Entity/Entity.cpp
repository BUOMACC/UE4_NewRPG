// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Components/CapsuleComponent.h"
#include "DamageCollider/DamageCollider.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NewRPGGameModeBase.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ʿ��� Ŀ���� ������Ʈ ����
	StatComp = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));

	MoveSpd = 600.f;
	bInvincible = false;
	bSuperArmor = true;
	bCanMove = true;
	bIsDead = false;

	GetCharacterMovement()->MaxWalkSpeed = MoveSpd;
}


void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float AEntity::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float CurrentDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	AEntity* Attacker = Cast<AEntity>(EventInstigator->GetPawn());
	if (Attacker == nullptr)
		return CurrentDamage;

	bool bIsCritical = Attacker->CalculateCritical();

	// ���������� ��� ���ظ� ����
	if (bInvincible) return CurrentDamage;

	// 1) ���ظ� ����
	if (CurrentDamage > 0)
	{
		// - ũ��Ƽ���� ��� ������ 1.5��
		if (bIsCritical)
			CurrentDamage *= 1.5f;

		// - ���¸�ŭ ������ ����
		CurrentDamage *= 1.f - (StatComp->GetDefence() / 100.f);
		StatComp->AddHealth(-CurrentDamage);

		if (StatComp->GetHealth() <= 0)
		{
			// - ��� ü���� �𿴴ٸ� ����
			Dead(EventInstigator->GetPawn());
		}
		else
		{
			// - �ƴ϶�� �ǰݾִϸ��̼� ���
			Attacker->OnHit(this, CurrentDamage);
		}
	}

	// 2) Knockback ��ġ��ŭ �����ڰ� �ٶ󺸴� �������� �о
	ADamageCollider* DamageCollider = Cast<ADamageCollider>(DamageCauser);
	if (!bSuperArmor && DamageCollider)
	{
		FVector LaunchDir = EventInstigator->GetPawn()->GetActorForwardVector();
		GetCharacterMovement()->Launch(LaunchDir * DamageCollider->KnockbackAmount);
	}

	// 3) �ǰ� �ִϸ��̼� ��� (SuperArmor ���¿����� ������� ����)
	//    �ǰݽ� �������� ����(������)�� ��ȯ���� �ൿ�� �Ұ����ϰ� ��
	if (!bSuperArmor && HitMontage)
	{
		AttackComp->SetComboTiming(false);
		AttackComp->SetIsAttack(true);
		PlayAnimMontage(HitMontage);
	}

	// 4) �ǰ��� ���� ������ ����� ��ġ�� ������ �ؽ�Ʈ ����
	ANewRPGGameModeBase* GM = Cast<ANewRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->SpawnDamageText(GetActorLocation(), CurrentDamage, bIsCritical);
	}

	return CurrentDamage;
}


void AEntity::OnHit(AEntity* Victim, float Damage)
{

}


void AEntity::Dead(AActor* Killer)
{
	bIsDead = true;

	// �浹�� ���� ���� �������ϰ���, ��Ʈ�ѷ��� ���
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetachFromControllerPendingDestroy();
}


float AEntity::CalculateDamage(float RatioAmount)
{
	return StatComp->GetStrength() * (RatioAmount / 100.f);
}


bool AEntity::CalculateCritical()
{
	float RNum = FMath::RandRange(0.01f, 1.f);
	float CritChance = (GetStatComponent()->GetCritChance() / 100.f);

	return RNum <= CritChance;
}

