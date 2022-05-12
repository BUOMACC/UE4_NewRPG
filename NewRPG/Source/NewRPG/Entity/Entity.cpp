// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Components/CapsuleComponent.h"
#include "DamageCollider/DamageCollider.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainGameMode.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	// 필요한 커스텀 컴포넌트 생성
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

	ADamageCollider* DamageCollider = Cast<ADamageCollider>(DamageCauser);
	AEntity* Attacker = Cast<AEntity>(EventInstigator->GetPawn());
	if (Attacker == nullptr)
		return CurrentDamage;

	bool bIsCritical = Attacker->CalculateCritical();

	// 무적상태인 경우 피해를 무시
	if (bInvincible) return CurrentDamage;

	// 1) 피해를 입음 (+MP 회복)
	if (CurrentDamage > 0)
	{
		// - 크리티컬일 경우 데미지 1.5배
		if (bIsCritical)
			CurrentDamage *= 1.5f;

		// - 방어력만큼 데미지 감소
		CurrentDamage *= 1.f - (StatComp->GetDefence() / 100.f);
		StatComp->AddHealth(-CurrentDamage);

		// - 공격자 MP회복 (기본 5 * 비율)
		Attacker->GetStatComponent()->AddMana(5 * (DamageCollider->ManaRatio / 100.f));

		if (StatComp->GetHealth() <= 0)
		{
			// - 모든 체력이 깎였다면 죽음
			Dead(EventInstigator->GetPawn());
		}
		else
		{
			// - 아니라면 피격애니메이션 재생
			Attacker->OnHit(this, CurrentDamage, DamageCollider->CameraClass);
		}
	}

	// 2) Knockback 수치만큼 공격자가 바라보는 방향으로 밀어냄
	if (!bSuperArmor && DamageCollider)
	{
		FVector LaunchDir = EventInstigator->GetPawn()->GetActorForwardVector();
		GetCharacterMovement()->Launch(LaunchDir * DamageCollider->KnockbackAmount);
	}

	// 3) 피격 애니메이션 재생 (SuperArmor 상태에서는 재생하지 않음)
	//    피격시 공격중인 상태(전투중)로 변환시켜 행동을 불가능하게 함
	if (!bSuperArmor && HitMontage)
	{
		AttackComp->SetComboTiming(false);
		AttackComp->SetIsAttack(true);
		PlayAnimMontage(HitMontage);
	}

	// 4) 피격자 기준 랜덤한 가까운 위치에 데미지 텍스트 생성
	AMainGameMode* GM = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->SpawnDamageText(GetActorLocation(), CurrentDamage, bIsCritical);
	}

	return CurrentDamage;
}


void AEntity::OnHit(AEntity* Victim, float Damage, TSubclassOf<UMatineeCameraShake> CameraClass)
{

}


void AEntity::Dead(AActor* Killer)
{
	bIsDead = true;

	// 애니메이션 중지충돌을 없애 길을 막지못하게함, 컨트롤러를 떼어냄
	StopAnimMontage();
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


