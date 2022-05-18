// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Data/ComboData.h"
#include "Entity/Entity.h"


UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComboIndex = -1;
	bComboTiming = true;
	bIsAttack = false;

	DefaultComboIndexL = 0;
	DefaultComboIndexR = 0;
}


void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 컴포넌트가 부착된 엔티티 설정
	OwnerComp = Cast<AEntity>(GetOwner());
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAttackComponent::AttackRandom(float PlaySpeed)
{
	// 콤보데이터 에셋이 있고, 콤보가 설정되어 있으며, 컴포넌트가 부착된 엔티티가 있고, 공격 가능한(콤보 가능한) 상태라면
	if (ComboData && ComboData->ComboList.Num() > 0 && OwnerComp && bComboTiming)
	{
		// 랜덤한 공격 애니메이션을 재생
		int32 RandomNum = FMath::RandRange(0, ComboData->ComboList.Num() - 1);
		UAnimMontage* RandomMontage = ComboData->ComboList[RandomNum].ComboAnimation;
		OwnerComp->PlayAnimMontage(RandomMontage, PlaySpeed);

		bComboTiming = false;
		bIsAttack = true;
	}
}


void UAttackComponent::AttackLeft(float PlaySpeed)
{
	// 콤보 타이밍이 아니면 (공격 가능한 상태 X)
	if (!bComboTiming)
		return;

	// 처음 공격하는 경우
	if (ComboIndex == -1)
	{
		PlayComboAnimByIndex(DefaultComboIndexL, PlaySpeed);
	}
	// 처음 공격하는게 아닌경우 (콤보를 이어나가는 경우)
	else
	{
		// 다음 왼쪽 콤보공격 인덱스를 가져옴
		int32 NextIndex = ComboData->ComboList[ComboIndex].NextComboIndexL;
		if (NextIndex >= 0)
		{
			PlayComboAnimByIndex(NextIndex, PlaySpeed);
		}
	}
}


void UAttackComponent::AttackRight(float PlaySpeed)
{
	// 콤보 타이밍이 아니면 (공격 가능한 상태 X)
	if (!bComboTiming)
		return;

	// 처음 공격하는 경우
	if (ComboIndex == -1)
	{
		PlayComboAnimByIndex(DefaultComboIndexR, PlaySpeed);
	}
	// 처음 공격하는게 아닌경우 (콤보를 이어나가는 경우)
	else
	{
		// 다음 왼쪽 콤보공격 인덱스를 가져옴
		int32 NextIndex = ComboData->ComboList[ComboIndex].NextComboIndexR;
		if (NextIndex >= 0)
		{
			PlayComboAnimByIndex(NextIndex, PlaySpeed);
		}
	}
}


void UAttackComponent::PlayComboAnimByIndex(int32 Index, float PlaySpeed)
{
	if (ComboData && ComboData->ComboList.Num() > Index)
	{
		UAnimMontage* ComboMontage = ComboData->ComboList[Index].ComboAnimation;
		if (ComboMontage)
		{
			ComboIndex = Index;
			OwnerComp->PlayAnimMontage(ComboMontage, PlaySpeed);
			bComboTiming = false;
			bIsAttack = true;
		}
	}
}


void UAttackComponent::CancelAttack()
{
	ComboIndex = -1;
	bComboTiming = true;
	bIsAttack = false;
}


float UAttackComponent::GetNextLeftComboCost()
{
	if (ComboIndex == -1)
		return 0.f;

	int32 NextIndex = ComboData->ComboList[ComboIndex].NextComboIndexL;
	if (NextIndex == -1)
		return 99999.f;
	return ComboData->ComboList[NextIndex].MPCost;
}


float UAttackComponent::GetNextRightComboCost()
{
	if (ComboIndex == -1)
		return 0.f;

	int32 NextIndex = ComboData->ComboList[ComboIndex].NextComboIndexR;
	if (NextIndex == -1)
		return 99999.f;
	return ComboData->ComboList[NextIndex].MPCost;
}
