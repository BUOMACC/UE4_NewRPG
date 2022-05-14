// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageObject.h"
#include "DamageBox.generated.h"

UCLASS()
class NEWRPG_API ADamageBox : public AActor, public IDamageObject
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

	UFUNCTION(BlueprintCallable)
	virtual void SetData(class AEntity* WhoSpawned, int32 DmgRatio, int32 MpRatio, float Knockback, float LifeTime, TSubclassOf<UMatineeCameraShake> NewCameraClass) override;
};
