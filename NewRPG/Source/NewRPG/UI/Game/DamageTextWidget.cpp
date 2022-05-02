// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidget.h"
#include "Components/TextBlock.h"


void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(OutAnim, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, true);
}


void UDamageTextWidget::SetDamageText(float Amount, bool bIsCritical)
{
	// float ������ �������� ������ �̿��� �ؽ�Ʈ�� ��ȯ
	FTextFormat Format = FTextFormat(FText::FromString(TEXT("{0}")));
	FText ResultText = FText::Format(Format, (int)Amount);
	Text_Damage->SetText(ResultText);

	// ũ��Ƽ������ ���� ����ȯ
	if (bIsCritical)
	{
		Text_Damage->SetColorAndOpacity(CriticalColor);
	}
	else
	{
		Text_Damage->SetColorAndOpacity(NormalColor);
	}
}