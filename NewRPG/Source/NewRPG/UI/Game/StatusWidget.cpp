// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Entity/StatComponent.h"
#include "Entity/Entity.h"


void UStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HealthBar->PercentDelegate.BindUFunction(this, FName("OnHealthBarChanged"));
	ManaBar->PercentDelegate.BindUFunction(this, FName("OnManaBarChanged"));
	StaminaBar->PercentDelegate.BindUFunction(this, FName("OnStaminaBarChanged"));
	Text_CName->TextDelegate.BindUFunction(this, FName("OnCNameChanged"));
}


void UStatusWidget::SetPortrait(UTexture2D* Portrait)
{
	Image_Portrait->SetBrushFromTexture(Portrait, false);
}


float UStatusWidget::OnHealthBarChanged()
{
	APawn* TargetPawn = GetOwningPlayer()->GetPawn();
	if (TargetPawn)
	{
		AEntity* Target = Cast<AEntity>(GetOwningPlayer()->GetPawn());
		if (Target && Target->GetStatComponent())
		{
			int32 CurrentHealth = Target->GetStatComponent()->GetHealth();
			int32 MaxHealth = Target->GetStatComponent()->GetMaxHealth();
			return (float)CurrentHealth / MaxHealth;
		}
	}

	return 0.0f;
}


float UStatusWidget::OnManaBarChanged()
{
	APawn* TargetPawn = GetOwningPlayer()->GetPawn();
	if (TargetPawn)
	{
		AEntity* Target = Cast<AEntity>(GetOwningPlayer()->GetPawn());
		if (Target && Target->GetStatComponent())
		{
			int32 CurrentMana = Target->GetStatComponent()->GetMana();
			int32 MaxMana = Target->GetStatComponent()->GetMaxMana();
			return (float)CurrentMana / MaxMana;
		}
	}

	return 0.0f;
}


float UStatusWidget::OnStaminaBarChanged()
{
	APawn* TargetPawn = GetOwningPlayer()->GetPawn();
	if (TargetPawn)
	{
		AEntity* Target = Cast<AEntity>(GetOwningPlayer()->GetPawn());
		if (Target && Target->GetStatComponent())
		{
			int32 CurrentStamina = Target->GetStatComponent()->GetStamina();
			int32 MaxStamina = Target->GetStatComponent()->GetMaxStamina();
			return (float)CurrentStamina / MaxStamina;
		}
	}

	return 0.0f;
}


FText UStatusWidget::OnCNameChanged()
{
	APawn* TargetPawn = GetOwningPlayer()->GetPawn();
	if (TargetPawn)
	{
		AEntity* Target = Cast<AEntity>(GetOwningPlayer()->GetPawn());
		if (Target)
		{
			return Target->EntityName;
		}
	}
	return FText::FromString(TEXT(""));
}