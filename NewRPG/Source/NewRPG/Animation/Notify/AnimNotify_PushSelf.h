// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PushSelf.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Push Self"))
class NEWRPG_API UAnimNotify_PushSelf : public UAnimNotify
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere)
	float PushPower_Forward;

	UPROPERTY(EditAnywhere)
	float PushPower_Up;

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
