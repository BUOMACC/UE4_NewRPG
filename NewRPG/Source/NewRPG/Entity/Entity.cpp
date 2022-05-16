// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Controller/PlayerGameController.h"
#include "Components/CapsuleComponent.h"
#include "DamageObject/DamageObject.h"
#include "Entity/Player/BasePlayer.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "Entity/BuffComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameMode.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	// 필요한 커스텀 컴포넌트 생성
	StatComp = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	BuffComp = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));

	OriginSpd = 600.f;
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
	
	BuffComp->OnApplyBuff.BindUFunction(this, TEXT("OnApplyBuff"));
	BuffComp->OnExpireBuff.BindUFunction(this, TEXT("OnExpireBuff"));

	WaitToStart();
}


void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float AEntity::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float CurrentDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	IDamageObject* DamageObject = Cast<IDamageObject>(DamageCauser);
	AEntity* Attacker = Cast<AEntity>(EventInstigator->GetPawn());
	if (Attacker == nullptr && DamageObject == nullptr)
		return CurrentDamage;

	// ------------------|데미지 계산|-------------------
	// 무적상태인 경우 피해를 무시
	if (bInvincible)
		return CurrentDamage;

	// 크리티컬 피해인경우 데미지 1.5배
	bool bIsCritical = Attacker->CalculateCritical();
	if (bIsCritical)
		CurrentDamage *= 1.5f;
	// -------------------------------------------------


	// 1) 피해를 입음 (+MP 회복)
	if (CurrentDamage > 0)
	{
		// - 방어력만큼 데미지 감소
		//   * 방어력은 스텟 + 버프효과의 합산
		float Defence = StatComp->GetDefence() + BuffComp->GetBuffAmount(EBuffType::ArmorUP);
		Defence = FMath::Clamp(Defence, 0.f, 100.f);
		CurrentDamage *= 1.f - (Defence / 100.f);
		StatComp->AddHealth(-CurrentDamage);

		// - 공격자 MP회복 (기본 5 * 비율)
		Attacker->GetStatComponent()->AddMana(5 * (DamageObject->ManaRatio / 100.f));

		// - 버프/디버프 적용
		BuffComp->AddBuff(DamageObject->BuffData);

		// - 체력 체크
		if (StatComp->GetHealth() <= 0)
		{
			// - 모든 체력이 깎였다면 죽음
			Dead(EventInstigator->GetPawn());
		}
		else
		{
			// - 아니라면 넉백 + 피격애니메이션 재생 (슈퍼아머 상태가 아니면)
			if (!bSuperArmor && HitMontage)
			{
				FVector LaunchDir = EventInstigator->GetPawn()->GetActorForwardVector();
				GetCharacterMovement()->Launch(LaunchDir * DamageObject->KnockbackAmount);

				AttackComp->SetComboTiming(false);
				AttackComp->SetIsAttack(true);
				PlayAnimMontage(HitMontage);
			}
			// - Attacker에게 공격에 성공했다는 신호를 발생시킴
			Attacker->OnHit(this, CurrentDamage, DamageObject->CameraClass);
		}
	}

	// 2) 피격자 기준 랜덤한 가까운 위치에 데미지 텍스트 생성
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


void AEntity::OnApplyBuff(UBuffData* Buff, bool AlreadyHasBuff)
{
	// -버프효과를 UI에 표시하는 부분
	APlayerGameController* PC = Cast<APlayerGameController>(GetController());
	if (PC)
	{
		PC->GetHudWidget()->AddBuffIcon(Buff);
	}

	// * 만약 이미 적용중인 버프였다면, 효과를 재적용시키지 않음
	if (AlreadyHasBuff)
		return;

	// - 실제 버프효과 적용부분
	switch (Buff->BuffType)
	{
		// 1) 이동속도 버프 처리
	case EBuffType::Speed:
		float SpeedRatio = 1.f + (BuffComp->GetBuffAmount(EBuffType::Speed) / 100.f);
		GetCharacterMovement()->MaxWalkSpeed = OriginSpd * SpeedRatio;
		break;
	}
}


void AEntity::OnExpireBuff(UBuffData* Buff)
{
	switch (Buff->BuffType)
	{
		// 1) 이동속도 버프 처리
	case EBuffType::Speed:
		float SpeedRatio = 1.f + (BuffComp->GetBuffAmount(EBuffType::Speed) / 100.f);
		GetCharacterMovement()->MaxWalkSpeed = OriginSpd * SpeedRatio;
		break;
	}

	APlayerGameController* PC = Cast<APlayerGameController>(GetController());
	if (PC)
	{
		PC->GetHudWidget()->RemoveBuffIcon(Buff);
	}
}


float AEntity::CalculateDamage(float RatioAmount)
{
	// 버프 효과를 포함해 데미지계산
	return StatComp->GetStrength() * (1.f + BuffComp->GetBuffAmount(EBuffType::PowerUP) / 100.f)
								   * (RatioAmount / 100.f);
}


bool AEntity::CalculateCritical()
{
	float RNum = FMath::RandRange(0.01f, 1.f);
	float CritChance = (GetStatComponent()->GetCritChance() / 100.f);

	return RNum <= CritChance;
}


void AEntity::WaitToStart()
{
	AMainGameMode* GM = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (GM && GM->WaitTime > 0)
	{
		// 기다리는동안 이동과 공격을 막음
		AttackComp->SetComboTiming(false);
		bCanMove = false;

		// 플레이어인경우 HUD를 잠시동안 숨김
		ABasePlayer* Player = Cast<ABasePlayer>(this);
		APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Player && PC)
		{
			PC->ShowHud(false);
		}

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]()
		{
			AttackComp->SetComboTiming(true);
			bCanMove = true;
			if (Player && PC)
			{
				PC->ShowHud(true);
			}
		}), GM->WaitTime, false);
	}
}