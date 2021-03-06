// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageActor.h"
#include "DamageBox.generated.h"

UCLASS()
class NEWRPG_API ADamageBox : public ADamageActor
{
	GENERATED_BODY()
	
protected:	
	ADamageBox();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

public:
	UFUNCTION(BlueprintCallable)
	void SetBoxSize(FVector& BoxSize);
};
