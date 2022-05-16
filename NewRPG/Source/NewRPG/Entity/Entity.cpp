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

	// �ʿ��� Ŀ���� ������Ʈ ����
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

	// ------------------|������ ���|-------------------
	// ���������� ��� ���ظ� ����
	if (bInvincible)
		return CurrentDamage;

	// ũ��Ƽ�� �����ΰ�� ������ 1.5��
	bool bIsCritical = Attacker->CalculateCritical();
	if (bIsCritical)
		CurrentDamage *= 1.5f;
	// -------------------------------------------------


	// 1) ���ظ� ���� (+MP ȸ��)
	if (CurrentDamage > 0)
	{
		// - ���¸�ŭ ������ ����
		//   * ������ ���� + ����ȿ���� �ջ�
		float Defence = StatComp->GetDefence() + BuffComp->GetBuffAmount(EBuffType::ArmorUP);
		Defence = FMath::Clamp(Defence, 0.f, 100.f);
		CurrentDamage *= 1.f - (Defence / 100.f);
		StatComp->AddHealth(-CurrentDamage);

		// - ������ MPȸ�� (�⺻ 5 * ����)
		Attacker->GetStatComponent()->AddMana(5 * (DamageObject->ManaRatio / 100.f));

		// - ����/����� ����
		BuffComp->AddBuff(DamageObject->BuffData);

		// - ü�� üũ
		if (StatComp->GetHealth() <= 0)
		{
			// - ��� ü���� �𿴴ٸ� ����
			Dead(EventInstigator->GetPawn());
		}
		else
		{
			// - �ƴ϶�� �˹� + �ǰݾִϸ��̼� ��� (���۾Ƹ� ���°� �ƴϸ�)
			if (!bSuperArmor && HitMontage)
			{
				FVector LaunchDir = EventInstigator->GetPawn()->GetActorForwardVector();
				GetCharacterMovement()->Launch(LaunchDir * DamageObject->KnockbackAmount);

				AttackComp->SetComboTiming(false);
				AttackComp->SetIsAttack(true);
				PlayAnimMontage(HitMontage);
			}
			// - Attacker���� ���ݿ� �����ߴٴ� ��ȣ�� �߻���Ŵ
			Attacker->OnHit(this, CurrentDamage, DamageObject->CameraClass);
		}
	}

	// 2) �ǰ��� ���� ������ ����� ��ġ�� ������ �ؽ�Ʈ ����
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

	// �ִϸ��̼� �����浹�� ���� ���� �������ϰ���, ��Ʈ�ѷ��� ���
	StopAnimMontage();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetachFromControllerPendingDestroy();
}


void AEntity::OnApplyBuff(UBuffData* Buff, bool AlreadyHasBuff)
{
	// -����ȿ���� UI�� ǥ���ϴ� �κ�
	APlayerGameController* PC = Cast<APlayerGameController>(GetController());
	if (PC)
	{
		PC->GetHudWidget()->AddBuffIcon(Buff);
	}

	// * ���� �̹� �������� �������ٸ�, ȿ���� �������Ű�� ����
	if (AlreadyHasBuff)
		return;

	// - ���� ����ȿ�� ����κ�
	switch (Buff->BuffType)
	{
		// 1) �̵��ӵ� ���� ó��
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
		// 1) �̵��ӵ� ���� ó��
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
	// ���� ȿ���� ������ ���������
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
		// ��ٸ��µ��� �̵��� ������ ����
		AttackComp->SetComboTiming(false);
		bCanMove = false;

		// �÷��̾��ΰ�� HUD�� ��õ��� ����
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