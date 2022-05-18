// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuffData.generated.h"


UENUM(BlueprintType)
enum class EBuffType : uint8
{
	PowerUP,
	ArmorUP,
	Speed,
};


UCLASS()
class NEWRPG_API UBuffData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EBuffType BuffType;

	UPROPERTY(EditAnywhere)
	class UTexture2D* Icon;	// UI에 보여질 버프 아이콘

	UPROPERTY(EditAnywhere)
	bool bIsDebuff;			// 디버프 여부 (UI표시에 영향)

	UPROPERTY(EditAnywhere)
	float Amount;			// 비율 50 = 50% 증가,   -50 = 50% 감소
	 
	UPROPERTY(EditAnywhere)
	int32 Duration;			// 지속시간 10 = 10초
};
