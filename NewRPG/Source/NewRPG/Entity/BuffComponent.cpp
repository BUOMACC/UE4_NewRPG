// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "Data/BuffData.h"
#include "Kismet/KismetSystemLibrary.h"


UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 버프의 지속시간을 갱신할 타이머를 1초주기로 실행
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UBuffComponent::UpdateBuffDuration, 1.f, true);
}


void UBuffComponent::UpdateBuffDuration()
{
	if (Buffs.Num() == 0) return;

	int32 GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	for (int i = 0; i < Buffs.Num(); i++)
	{
		// 버프를 추가한 이후 지속시간만큼 흐른경우
		if (GameTime - StartTime[i] >= Buffs[i]->Duration)
		{
			// 버프를 목록에서 삭제
			RemoveBuff(i);
		}
	}
}


void UBuffComponent::CalcBuffAmount(EBuffType BuffType, float Amount)
{
	switch (BuffType)
	{
	case EBuffType::PowerUP:
		PowerUPAmount += Amount;
		break;

	case EBuffType::ArmorUP:
		ArmorUPAmount += Amount;
		ArmorUPAmount = FMath::Clamp(ArmorUPAmount, -100.f, 100.f);
		break;

	case EBuffType::Speed:
		SpeedAmount += Amount;
		SpeedAmount = FMath::Clamp(SpeedAmount, -100.f, 100.f);
		break;
	}
}


void UBuffComponent::AddBuff(UBuffData* NewBuff)
{
	if (NewBuff == nullptr) return;

	// 이미 적용중인 버프인지 체크
	int32 GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if (Buffs.Num() != 0)
	{
		for (int i = 0; i < Buffs.Num(); i++)
		{
			if (Buffs[i] != NewBuff)
				continue;

			// 중복된 버프라면 지속시간만 갱신
			StartTime[i] = GameTime;
			if (OnApplyBuff.IsBound())
			{
				OnApplyBuff.Execute(NewBuff, true);
			}
			return;
		}
	}
	CalcBuffAmount(NewBuff->BuffType, NewBuff->Amount);
	Buffs.Add(NewBuff);
	StartTime.Add(GameTime);
	if (OnApplyBuff.IsBound())
	{
		OnApplyBuff.Execute(NewBuff, false);
	}
}


void UBuffComponent::RemoveBuff(int32 BuffIndex)
{
	if (Buffs[BuffIndex] == nullptr) return;

	CalcBuffAmount(Buffs[BuffIndex]->BuffType, -Buffs[BuffIndex]->Amount);
	if (OnExpireBuff.IsBound())
	{
		OnExpireBuff.Execute(Buffs[BuffIndex]);
	}

	Buffs.RemoveAt(BuffIndex);
	StartTime.RemoveAt(BuffIndex);
}


float UBuffComponent::GetBuffAmount(EBuffType BuffType)
{
	switch (BuffType)
	{
	case EBuffType::PowerUP:
		return PowerUPAmount;

	case EBuffType::ArmorUP:
		return ArmorUPAmount;

	case EBuffType::Speed:
		return SpeedAmount;
	}
	return 0.f;
}