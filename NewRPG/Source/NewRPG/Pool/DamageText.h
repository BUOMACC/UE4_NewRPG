// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageText.generated.h"

UCLASS()
class NEWRPG_API ADamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageText();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* DTWidgetComponent;

	UPROPERTY(EditAnywhere)
	float VisibleTime;

	FTimerHandle TimerHandle;

public:
	class AMainGameMode* PoolRef;

	void EnqueuePool();
	void SetEnable(bool Flag);
	void SetDamageText(float DamageAmount, bool bIsCritical);
};
