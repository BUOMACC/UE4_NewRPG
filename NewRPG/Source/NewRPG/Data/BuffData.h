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
	class UTexture2D* Icon;	// UI�� ������ ���� ������

	UPROPERTY(EditAnywhere)
	bool bIsDebuff;			// ����� ���� (UIǥ�ÿ� ����)

	UPROPERTY(EditAnywhere)
	float Amount;			// ���� 50 = 50% ����,   -50 = 50% ����
	 
	UPROPERTY(EditAnywhere)
	int32 Duration;			// ���ӽð� 10 = 10��
};
