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

	// * SpringArmComponent ����
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 8.f;
	SpringArmComp->TargetArmLength = 450.f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 60.f), FRotator(-35.f, 0.f, 0.f));
	SpringArmComp->bUsePawnControlRotation = true;

	// * CameraComponent ����
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	// * �⺻ Character Data Table ����
	static ConstructorHelpers::FObjectFinder<UDataTable> DefaultCharacterTable(TEXT("DataTable'/Game/Data/Entity/CharacterDataTable.CharacterDataTable'"));
	if (DefaultCharacterTable.Succeeded())
	{
		CharacterTable = DefaultCharacterTable.Object;
	}

	// * �⺻ Mesh ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultCharacterMesh(TEXT("SkeletalMesh'/Game/Models/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun'"));
	if (DefaultCharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(DefaultCharacterMesh.Object);
	}

	// * �⺻ Animation ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> DefaultCharacterAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/Character/Kwang/ABP_Kwang.ABP_Kwang_C'"));
	if (DefaultCharacterAnim.Succeeded())
	{
		GetMesh()->AnimClass = DefaultCharacterAnim.Class;
	}

	// * CharacterMovement ����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 480.f;

	GetCharacterMovement()->MaxAcceleration = 4096.f;
	GetCharacterMovement()->BrakingFrictionFactor = 4.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;


	// * �ʱ�ȭ
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
	// �������̶�� ��� ��ȯ�� �Ұ����ϰ� ��
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
	// ���׹̳ʰ� �����ϴٸ� ���
	if (StatComp->GetStamina() < RollingDecStamina) return;

	// �ִϸ��̼��� �ִ°��
	//  * ������ �ִϸ��̼��� ���
	//  * �Է� ������ �������� ĳ���͸� ȸ��
	if (bCanMove && RollingMontage && AttackComp->GetComboTiming() && !GetCharacterMovement()->IsFalling())
	{
		PlayAnimMontage(RollingMontage, 1.2f * (1 + RollingSpeed / 100.f));

		// AttackComponent�� ComboTiming�� true�� �ٲ�
		// -> ������ ���� ������ �Ұ����� ����
		bRolling = true;
		bInvincible = true;
		AttackComp->SetComboTiming(false);
		FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + RollingDirForward + RollingDirRight);
		SetActorRotation(TargetRot);

		// ���׹̳ʸ� ����, �̵��ӵ� ����
		StatComp->AddStamina(-RollingDecStamina);
		GetCharacterMovement()->MaxWalkSpeed = RollingMoveSpeed;

		// RollingTime�� �ڿ� ������ ����
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
	// ���ݵ��� �����⸦ ����Ҽ� �ֱ⶧���� AttackComponent ���� ������ �ʱ�ȭ
	// -> �ٽ� ������ ������ ���°���
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