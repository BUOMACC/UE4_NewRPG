// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffIcon.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/BuffData.h"
#include "Kismet/KismetSystemLibrary.h"


void UBuffIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Duration > 0)
	{
		Duration -= InDeltaTime;
		Duration = FMath::Clamp(Duration, 0.f, Duration);
		Text_Duration->SetText(FText::AsNumber((int)Duration));
	}
}


void UBuffIcon::SetBuffData(UBuffData* Data)
{
	if (Data == nullptr)
		return;

	BuffData = Data;
	Duration = BuffData->Duration;

	Image_Icon->SetBrushFromTexture(Data->Icon, false);
	// 디버프인 경우 테두리 색상변경
	if (Data->bIsDebuff)
	{
		Outline->SetBrushColor(DebuffOutlineColor);
	}
}