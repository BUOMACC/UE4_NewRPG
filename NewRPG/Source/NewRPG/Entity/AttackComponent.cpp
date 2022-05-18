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
	
	// ������Ʈ�� ������ ��ƼƼ ����
	OwnerComp = Cast<AEntity>(GetOwner());
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAttackComponent::AttackRandom(float PlaySpeed)
{
	// �޺������� ������ �ְ�, �޺��� �����Ǿ� ������, ������Ʈ�� ������ ��ƼƼ�� �ְ�, ���� ������(�޺� ������) ���¶��
	if (ComboData && ComboData->ComboList.Num() > 0 && OwnerComp && bComboTiming)
	{
		// ������ ���� �ִϸ��̼��� ���
		int32 RandomNum = FMath::RandRange(0, ComboData->ComboList.Num() - 1);
		UAnimMontage* RandomMontage = ComboData->ComboList[RandomNum].ComboAnimation;
		OwnerComp->PlayAnimMontage(RandomMontage, PlaySpeed);

		bComboTiming = false;
		bIsAttack = true;
	}
}


void UAttackComponent::AttackLeft(float PlaySpeed)
{
	// �޺� Ÿ�̹��� �ƴϸ� (���� ������ ���� X)
	if (!bComboTiming)
		return;

	// ó�� �����ϴ� ���
	if (ComboIndex == -1)
	{
		PlayComboAnimByIndex(DefaultComboIndexL, PlaySpeed);
	}
	// ó�� �����ϴ°� �ƴѰ�� (�޺��� �̾���� ���)
	else
	{
		// ���� ���� �޺����� �ε����� ������
		int32 NextIndex = ComboData->ComboList[ComboIndex].NextComboIndexL;
		if (NextIndex >= 0)
		{
			PlayComboAnimByIndex(NextIndex, PlaySpeed);
		}
	}
}


void UAttackComponent::AttackRight(float PlaySpeed)
{
	// �޺� Ÿ�̹��� �ƴϸ� (���� ������ ���� X)
	if (!bComboTiming)
		return;

	// ó�� �����ϴ� ���
	if (ComboIndex == -1)
	{
		PlayComboAnimByIndex(DefaultComboIndexR, PlaySpeed);
	}
	// ó�� �����ϴ°� �ƴѰ�� (�޺��� �̾���� ���)
	else
	{
		// ���� ���� �޺����� �ε����� ������
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
