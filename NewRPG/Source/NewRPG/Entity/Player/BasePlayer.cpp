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
#include "Entity/InteractActor.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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


void ABasePlayer::ToggleBattleMode()
{
	// 공격중이라면 모드 전환을 불가능하게 함
	if (AttackComp->GetIsAttack()) return;
	if (AttackComp->GetComboTiming() == false) return;
	if (GetCharacterMovement()->IsFalling()) return;
	
	if (bBattleMode)
	{
		if (TravelStartMontage)
		{
			AttackComp->SetComboTiming(false);
			PlayAnimMontage(TravelStartMontage, 1.0f);
			GetCharacterMovement()->MaxWalkSpeed = MoveSpd;
		}
	}
	else
	{
		AttackComp->AttackLeft(1.0f + (StatComp->GetASpeed() / 100.f));
		GetCharacterMovement()->MaxWalkSpeed = BattleMoveSpd;
	}
	bBattleMode = !bBattleMode;
}


void ABasePlayer::ShakeCamera(TSubclassOf<UMatineeCameraShake> ShakeData)
{
	if (ShakeData == nullptr) return;


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
	}
}


UTexture2D* ABasePlayer::GetPortrait()
{
	if (CharacterTable == nullptr) return nullptr;

	FCharacterDataRow* CharacterRow = CharacterTable->FindRow<FCharacterDataRow>(FName(*EntityName.ToString()), TEXT(""));
	if (CharacterRow)
	{
		return CharacterRow->Portrait;
	}
	return nullptr;
}


void ABasePlayer::OnHit(AEntity* Victim, float Damage)
{
	ShakeCamera(UCameraShakeHit_Low::StaticClass());
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
	if (StatComp->GetStamina() < RollingDecStamina) return;

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
	GetCharacterMovement()->MaxWalkSpeed = (bBattleMode) ? BattleMoveSpd : MoveSpd;
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
	if (bCanMove && bBattleMode && !bRolling)
	{
		AttackComp->AttackLeft(1.0f + (StatComp->GetASpeed() / 100.f));

		FRotator StartRot = GetActorRotation();
		FRotator EndRot = GetControlRotation();

		FRotator TargetRot = FMath::Lerp(StartRot, EndRot, 0.1f);
		SetActorRotation(FRotator(StartRot.Roll, TargetRot.Yaw, StartRot.Pitch));
	}
}


void ABasePlayer::AttackRight()
{
	if (bCanMove && bBattleMode && !bRolling)
	{
		AttackComp->AttackRight(1.0f + (StatComp->GetASpeed() / 100.f));

		FRotator StartRot = GetActorRotation();
		FRotator EndRot = GetControlRotation();

		FRotator TargetRot = FMath::Lerp(StartRot, EndRot, 0.1f);
		SetActorRotation(FRotator(StartRot.Roll, TargetRot.Yaw, StartRot.Pitch));
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
	if (InteractActor == nullptr) return;

	IInteractActor* IActor = Cast<IInteractActor>(InteractActor);
	if (IActor)
	{
		IActor->Interact();
	}
}


void ABasePlayer::SettingStatFromTable()
{
	if (CharacterTable == nullptr) return;

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
	}

	StatComp->HealAll();
}