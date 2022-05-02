// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Entity/Entity.h"
#include "Entity/StatComponent.h"


void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 이름 표시
	Text_EntityName->SetText(OwnerEntity->EntityName);
}


void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	RefreshHealthBar();
}


void UHealthBarWidget::RefreshHealthBar()
{
	// HealthBar_Front의 체력을 깎음
	float Percentage = 0.f;
	if (OwnerEntity && OwnerEntity->GetStatComponent())
	{
		float MaxHealth = OwnerEntity->GetStatComponent()->GetMaxHealth();
		float CurHealth = OwnerEntity->GetStatComponent()->GetHealth();
		Percentage = CurHealth / MaxHealth;
	}
	HealthBar_Front->SetPercent(Percentage);

	// HealthBar_Back의 퍼센트는 HealthBar_Front를 부드럽게 따라가도록 함
	float TargetPercent = FMath::Lerp(HealthBar_Back->Percent, HealthBar_Front->Percent, 0.03f);
	if (FMath::Abs(TargetPercent - HealthBar_Front->Percent) <= 0.02f)
		TargetPercent = HealthBar_Front->Percent;

	HealthBar_Back->SetPercent(TargetPercent);
}
