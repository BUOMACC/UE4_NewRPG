// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Entity/Entity.h"
#include "Entity/StatComponent.h"


void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �̸� ǥ��
	Text_EntityName->SetText(OwnerEntity->EntityName);
}


void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	RefreshHealthBar();
}


void UHealthBarWidget::RefreshHealthBar()
{
	// HealthBar_Front�� ü���� ����
	float Percentage = 0.f;
	if (OwnerEntity && OwnerEntity->GetStatComponent())
	{
		float MaxHealth = OwnerEntity->GetStatComponent()->GetMaxHealth();
		float CurHealth = OwnerEntity->GetStatComponent()->GetHealth();
		Percentage = CurHealth / MaxHealth;
	}
	HealthBar_Front->SetPercent(Percentage);

	// HealthBar_Back�� �ۼ�Ʈ�� HealthBar_Front�� �ε巴�� ���󰡵��� ��
	float TargetPercent = FMath::Lerp(HealthBar_Back->Percent, HealthBar_Front->Percent, 0.03f);
	if (FMath::Abs(TargetPercent - HealthBar_Front->Percent) <= 0.02f)
		TargetPercent = HealthBar_Front->Percent;

	HealthBar_Back->SetPercent(TargetPercent);
}
