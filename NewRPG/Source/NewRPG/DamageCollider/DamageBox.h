// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageCollider.h"
#include "DamageBox.generated.h"

UCLASS()
class NEWRPG_API ADamageBox : public ADamageCollider
{
	GENERATED_BODY()
	
public:	
	ADamageBox();

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

public:
	UFUNCTION(BlueprintCallable)
	void SetBoxSize(FVector& BoxSize);
};
