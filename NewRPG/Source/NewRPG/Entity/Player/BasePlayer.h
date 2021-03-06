// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Entity.h"
#include "Struct/ItemStat.h"
#include "BasePlayer.generated.h"

UCLASS()
class NEWRPG_API ABasePlayer : public AEntity
{
	GENERATED_BODY()

public:
	ABasePlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnHit(AEntity* Victim, float Damage, TSubclassOf<UMatineeCameraShake> CameraClass) override;
	virtual void Dead(AActor* Killer) override;

protected:
	// 캐릭터의 정보를 담고있는 Table
	UPROPERTY(EditAnywhere, Category = "Entity Data")
	class UDataTable* CharacterTable;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

public:
	// 공격모드 상태인지 가져옴
	UFUNCTION(BlueprintPure, Category = "Character State")
	bool GetBattleMode() const { return bBattleMode; }

	// 공격모드 설정
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetBattleMode(bool BattleMode) { bBattleMode = BattleMode; }

	// 공격모드를 Toggle로 설정
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void ToggleBattleMode();

	// 카메라 Shake
	UFUNCTION(BlueprintCallable, Category = "Character")
	void ShakeCamera(TSubclassOf<UMatineeCameraShake> ShakeData);

	// 추가 스텟적용
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SettingExtraStat();

	// 초상화(프로필 사진) 반환
	UFUNCTION(BlueprintPure)
	UTexture2D* GetPortrait();

private:
	// 이동
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void TurnRight(float Axis);
	void LookUp(float Axis);

	void RollingStart();
	void RollingEnd();
	void RollingMove();

	void AttackLeft();
	void AttackRight();

	void TryInteract();
	void Interact();

	void HealStamina(float DeltaTime);

	// Character Table로부터 받은 정보를 기반으로 스텟을 설정함
	void SettingStatFromTable();

private:
	// 공격모드에서 이동속도
	float BattleMoveSpd;

	// 구르기 속도, 구를때 이동속도, 구르기 지속시간, 소모 스테미너
	float RollingSpeed;
	float RollingMoveSpeed;
	float RollingTime;
	float RollingDecStamina;

	// 구르기 임시 정보
	FVector RollingDirForward;
	FVector RollingDirRight;
	FVector RollingDir;

	// 기본모드 or 공격모드 여부 (false = 기본모드)
	bool bBattleMode;
	// 구르는 중인지
	bool bRolling;

	// 공격모드 -> 기본모드로 전환할때 실행되는 애니메이션
	class UAnimMontage* TravelStartMontage;

	// 구를때(회피) 애니메이션
	class UAnimMontage* RollingMontage;

	// 상호작용 액터
	AActor* InteractActor;

	// 스테미너 회복시간 (얼마나 스테미너를 사용하지 않아야 회복할지)
	float Heal_Stamina_Time;
	// 남은 스테미너 회복시간
	float Remain_Stamina_Time;
	// 초당 스테미너 회복량
	float Heal_Stamina_PerSec;
};
