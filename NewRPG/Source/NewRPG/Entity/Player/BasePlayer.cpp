// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Controller/PlayerGameController.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraShake/CameraShakeHit_Low.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Entity/AttackComponent.h"
#include "Entity/StatComponent.h"
#include "Entity/BuffComponent.h"
#include "Entity/InteractActor.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainGameMode.h"
#include "Struct/CharacterDataRow.h"
#include "Struct/ItemStat.h"


ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCollisionProfileName("Player");

	// * SpringArmComponent 생성
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 8.f;
	SpringArmComp->TargetArmLength = 450.f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 60.f), FRotator(-35.f, 0.f, 0.f));
	SpringArmComp->bUsePawnControlRotation = true;

	// * CameraComponent 생성
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	// * 기본 Mesh 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// * CharacterMovement 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 480.f;

	GetCharacterMovement()->MaxAcceleration = 4096.f;
	GetCharacterMovement()->BrakingFrictionFactor = 4.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;


	// * 초기화
	bBattleMode = false;
	bRolling = false;
	MoveSpd = 600.f;
	BattleMoveSpd = 480.f;
	RollingSpeed = 1.f;
	RollingMoveSpeed = 600.f;
	RollingTime = 0.9f;

	RollingDirForward = FVector::ZeroVector;
	RollingDirRight = FVector::ZeroVector;

	Heal_Stamina_Time = 1.5f;
	Remain_Stamina_Time = 1.5f;
	Heal_Stamina_PerSec = 10.f;
}


void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	SettingStatFromTable();
	SettingExtraStat();
}


void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RollingMove();
	TryInteract();
	HealStamina(DeltaTime);
}


void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::LookUp);

	PlayerInputComponent->BindAction("BattleMode", IE_Pressed, this, &ABasePlayer::ToggleBattleMode);
	PlayerInputComponent->BindAction("Rolling", IE_Pressed, this, &ABasePlayer::RollingStart);
	PlayerInputComponent->BindAction("AttackLeft", IE_Pressed, this, &ABasePlayer::AttackLeft);
	PlayerInputComponent->BindAction("AttackRight", IE_Pressed, this, &ABasePlayer::AttackRight);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasePlayer::Interact);
}


void ABasePlayer::Dead(AActor* Killer)
{
	Super::Dead(Killer);

	// 플레이중에 플레이어가 죽은경우, 게임모드에 클리어를 실패했다고 알림
	AMainGameMode* GM = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->GameOver();
	}
}


void ABasePlayer::OnHit(AEntity* Victim, float Damage, TSubclassOf<UMatineeCameraShake> CameraClass)
{
	ShakeCamera(CameraClass);
}


void ABasePlayer::ToggleBattleMode()
{
	// 공격중이라면 모드 전환을 불가능하게 함
	if (AttackComp->GetIsAttack()
		|| AttackComp->GetComboTiming() == false
		|| GetCharacterMovement()->IsFalling())
		return;
	
	if (bBattleMode)
	{
		if (TravelStartMontage)
		{
			AttackComp->SetComboTiming(false);
			PlayAnimMontage(TravelStartMontage, 1.0f);
			OriginSpd = MoveSpd;
			GetCharacterMovement()->MaxWalkSpeed = OriginSpd * (1.f + (BuffComp->GetBuffAmount(EBuffType::Speed) / 100.f));
			
		}
	}
	else
	{
		AttackComp->AttackLeft(1.0f + (StatComp->GetASpeed() / 100.f));
		OriginSpd = BattleMoveSpd;
		GetCharacterMovement()->MaxWalkSpeed = OriginSpd * (1.f + (BuffComp->GetBuffAmount(EBuffType::Speed) / 100.f));
	}
	bBattleMode = !bBattleMode;
}


void ABasePlayer::ShakeCamera(TSubclassOf<UMatineeCameraShake> ShakeData)
{
	if (ShakeData == nullptr)
		return;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->PlayerCameraManager->PlayCameraShake(ShakeData, 1.0f);
	}
}


void ABasePlayer::SettingExtraStat()
{
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	FItemStat& ExtraStat = Data->StatData;
	if (Data)
	{
		StatComp->SetMaxHealth(StatComp->GetOriginHealth() + ExtraStat.Health);
		StatComp->SetStrength(StatComp->GetOriginStrength() + ExtraStat.Strength);
		StatComp->SetDefence(StatComp->GetOriginDefence() + ExtraStat.Defence);
		StatComp->SetCritChance(StatComp->GetOriginCritChance() + ExtraStat.CritChance);
		StatComp->SetASpeed(StatComp->GetOriginASpeed() + ExtraStat.AttackSpd);

		StatComp->HealAll();
	}
}


UTexture2D* ABasePlayer::GetPortrait()
{
	if (CharacterTable == nullptr)
		return nullptr;

	FCharacterDataRow* CharacterRow = CharacterTable->FindRow<FCharacterDataRow>(FName(*EntityName.ToString()), TEXT(""));
	if (CharacterRow)
	{
		return CharacterRow->Portrait;
	}
	return nullptr;
}


void ABasePlayer::MoveForward(float Axis)
{
	FRotator YawRot = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector Dir = FRotationMatrix(YawRot).GetScaledAxis(EAxis::X);

	RollingDirForward = Dir * Axis;

	if (!GetAttackComponent()->GetIsAttack() && bCanMove && !bRolling)
	{
		AddMovementInput(Dir, Axis);
	}
}


void ABasePlayer::MoveRight(float Axis)
{
	FRotator YawRot = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector Dir = FRotationMatrix(YawRot).GetScaledAxis(EAxis::Y);

	RollingDirRight = Dir * Axis;

	if (!GetAttackComponent()->GetIsAttack() && bCanMove && !bRolling)
	{
		AddMovementInput(Dir, Axis);
	}
}


void ABasePlayer::TurnRight(float Axis)
{
	AddControllerYawInput(Axis);
}


void ABasePlayer::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}


void ABasePlayer::RollingStart()
{
	// 스테미너가 부족하다면 취소
	if (StatComp->GetStamina() < RollingDecStamina)
		return;

	// 애니메이션이 있는경우
	//  * 구르기 애니메이션을 재생
	//  * 입력 방향을 기준으로 캐릭터를 회전
	if (bCanMove && RollingMontage && AttackComp->GetComboTiming() && !GetCharacterMovement()->IsFalling())
	{
		PlayAnimMontage(RollingMontage, 1.2f * (1 + RollingSpeed / 100.f));

		// AttackComponent의 ComboTiming을 true로 바꿈
		// -> 구르는 도중 공격이 불가능한 상태
		bRolling = true;
		bInvincible = true;
		Remain_Stamina_Time = Heal_Stamina_Time;
		AttackComp->SetComboTiming(false);
		FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + RollingDirForward + RollingDirRight);
		SetActorRotation(TargetRot);

		// 스테미너를 깎음, 이동속도 조정
		StatComp->AddStamina(-RollingDecStamina);
		GetCharacterMovement()->MaxWalkSpeed = RollingMoveSpeed;

		// RollingTime초 뒤에 구르기 종료
		FTimerHandle RollingTimer;
		GetWorldTimerManager().SetTimer(RollingTimer, this, &ABasePlayer::RollingEnd, RollingTime * (1 - RollingSpeed / 100.f), false, RollingTime * (1 - RollingSpeed / 100.f));;
	}
}


void ABasePlayer::RollingEnd()
{
	if (RollingMontage)
	{
		StopAnimMontage(RollingMontage);
	}
	// 공격도중 구르기를 사용할수 있기때문에 AttackComponent 관련 변수를 초기화
	// -> 다시 공격이 가능한 상태가됨
	OriginSpd = (bBattleMode) ? BattleMoveSpd : MoveSpd;
	GetCharacterMovement()->MaxWalkSpeed = OriginSpd * (1.f + (BuffComp->GetBuffAmount(EBuffType::Speed) / 100.f));
	bRolling = false;
	bInvincible = false;
	AttackComp->CancelAttack();
	RollingDir = FVector::ZeroVector;
}


void ABasePlayer::RollingMove()
{
	if (bRolling)
	{
		AddMovementInput(GetActorForwardVector(), 1.f);
	}
}


void ABasePlayer::AttackLeft()
{
	// 이동이 가능 & 전투모드 & 구르기중이 아니고 & 콤보가 가능한 상태면
	if (bCanMove && bBattleMode && !bRolling && AttackComp->GetComboTiming())
	{
		// MP Check
		if (StatComp->GetMana() >= AttackComp->GetNextLeftComboCost())
		{
			StatComp->AddMana(-AttackComp->GetNextLeftComboCost());
			AttackComp->AttackLeft(1.0f + (StatComp->GetASpeed() / 100.f));

			FRotator StartRot = GetActorRotation();
			FRotator EndRot = GetControlRotation();

			FRotator TargetRot = FMath::Lerp(StartRot, EndRot, 0.15f);
			SetActorRotation(FRotator(StartRot.Roll, TargetRot.Yaw, StartRot.Pitch));
		}
	}
}


void ABasePlayer::AttackRight()
{
	if (bCanMove && bBattleMode && !bRolling && AttackComp->GetComboTiming())
	{
		// MP Check
		if (StatComp->GetMana() >= AttackComp->GetNextRightComboCost())
		{
			StatComp->AddMana(-AttackComp->GetNextRightComboCost());
			AttackComp->AttackRight(1.0f + (StatComp->GetASpeed() / 100.f));

			FRotator StartRot = GetActorRotation();
			FRotator EndRot = GetControlRotation();

			FRotator TargetRot = FMath::Lerp(StartRot, EndRot, 0.15f);
			SetActorRotation(FRotator(StartRot.Roll, TargetRot.Yaw, StartRot.Pitch));
		}
	}
}


void ABasePlayer::TryInteract()
{
	APlayerCameraManager* CM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	APlayerGameController* PC = Cast<APlayerGameController>(GetController());
	FHitResult Hit;
	FVector Start = CM->GetCameraLocation();
	FVector End = Start + CM->GetActorForwardVector() * 1000.f;
	bool Success = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel7);
	if (Success)
	{
		InteractActor = Hit.GetActor();
		if (PC) PC->ShowInteractMark(true);
	}
	else
	{
		InteractActor = nullptr;
		if (PC) PC->ShowInteractMark(false);
	}
}


void ABasePlayer::Interact()
{
	if (InteractActor == nullptr)
		return;

	IInteractActor* IActor = Cast<IInteractActor>(InteractActor);
	if (IActor)
	{
		IActor->Interact();
	}
}


void ABasePlayer::HealStamina(float DeltaTime)
{
	if (Remain_Stamina_Time <= 0)
	{
		StatComp->AddStamina(Heal_Stamina_PerSec * DeltaTime);
		return;
	}
	Remain_Stamina_Time -= DeltaTime;
}


void ABasePlayer::SettingStatFromTable()
{
	if (CharacterTable == nullptr)
		return;

	FCharacterDataRow* CharacterRow = CharacterTable->FindRow<FCharacterDataRow>(FName(*EntityName.ToString()), TEXT(""));
	if (CharacterRow)
	{
		StatComp->SetStrength(CharacterRow->Strength);
		StatComp->SetMaxHealth(CharacterRow->Health);
		StatComp->SetMaxMana(CharacterRow->Mana);
		StatComp->SetMaxStamina(CharacterRow->Stamina);
		StatComp->SetDefence(CharacterRow->Defence);
		StatComp->SetCritChance(CharacterRow->CritChance);
		StatComp->SetASpeed(CharacterRow->AttackSpeed);

		MoveSpd = CharacterRow->MoveSpd;
		OriginSpd = MoveSpd;
		TravelStartMontage = CharacterRow->TravelStartMontage;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpd;

		BattleMoveSpd = CharacterRow->BattleMoveSpd;
		
		RollingSpeed = CharacterRow->RollingSpeed;
		RollingMoveSpeed = CharacterRow->RollingMoveSpeed;
		RollingDecStamina = CharacterRow->RollingDecStamina;
		RollingMontage = CharacterRow->RollingMontage;

		bInvincible = CharacterRow->Invincible;
		bSuperArmor = CharacterRow->SuperArmor;

		HitMontage = CharacterRow->HitMontage;
		HitSound = CharacterRow->HitSound;

		Heal_Stamina_Time = CharacterRow->Heal_Stamina_Time;
		Remain_Stamina_Time = Heal_Stamina_Time;
		Heal_Stamina_PerSec = CharacterRow->Heal_Stamina_PerSec;
	}

	StatComp->InitOriginStat();
	StatComp->HealAll();
}