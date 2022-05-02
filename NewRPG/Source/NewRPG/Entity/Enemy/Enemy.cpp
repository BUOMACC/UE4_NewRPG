// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Enemy/Enemy.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entity/StatComponent.h"
#include "Entity/AttackComponent.h"
#include "Struct/EnemyDataRow.h"
#include "UI/Game/HealthBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName("Enemy");

	// * �⺻ Enemy Data Table ����
	static ConstructorHelpers::FObjectFinder<UDataTable> DefaultEnemyTable(TEXT("DataTable'/Game/Data/Entity/EnemyDataTable.EnemyDataTable'"));
	if (DefaultEnemyTable.Succeeded())
	{
		EnemyTable = DefaultEnemyTable.Object;
	}

	// * ü�� ǥ�ø� ���� WidgetComponent ����
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetupAttachment(GetMesh());
	HealthBarWidget->SetRelativeLocation(FVector(0, 0, 220.0f));
	HealthBarWidget->SetDrawSize(FVector2D(100.f, 5.f));

	// * �⺻ Mesh ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultEnemyMesh(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	if (DefaultEnemyMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(DefaultEnemyMesh.Object);
	}

	// * �⺻ Animation ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> DefaultEnemyAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/Enemy/Gideon/ABP_Gideon.ABP_Gideon_C'"));
	if (DefaultEnemyAnim.Succeeded())
	{
		GetMesh()->AnimClass = DefaultEnemyAnim.Class;
	}

	// * CharacterMovement ����
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;


	// * �ʱ�ȭ
}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SettingStatFromTable();
	SettingHealthBar();
}


void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemy::SettingStatFromTable()
{
	if (EnemyTable == nullptr) return;
	FEnemyDataRow* EnemyRow = EnemyTable->FindRow<FEnemyDataRow>(FName(*EntityName.ToString()), TEXT(""));
	if (EnemyRow)
	{
		StatComp->SetStrength(EnemyRow->Strength);
		StatComp->SetMaxHealth(EnemyRow->Health);
		StatComp->SetMaxMana(EnemyRow->Mana);
		StatComp->SetMaxStamina(EnemyRow->Stamina);

		MoveSpd = EnemyRow->MoveSpd;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpd;

		bInvincible = EnemyRow->Invincible;
		bSuperArmor = EnemyRow->SuperArmor;

		HitMontage = EnemyRow->HitMontage;
	}

	StatComp->HealAll();
}


void AEnemy::SettingHealthBar()
{
	UUserWidget* CurWidget = HealthBarWidget->GetUserWidgetObject();
	if (CurWidget)
	{
		UHealthBarWidget* HpWidget = Cast<UHealthBarWidget>(CurWidget);
		if (HpWidget)
		{
			HpWidget->SetOwnerEntity(this);
		}
	}
}


void AEnemy::Dead(AActor* Killer)
{
	Super::Dead(Killer);

	// ������ ü�¹ٸ� ������ �ʰ���
	HealthBarWidget->SetVisibility(false);
}