// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ComboTiming.generated.h"

/**
 * 다음 콤보를 이어가기 위해 콤보가능 상태를 변경하는 Notify
 * ComboTiming 변수가 true인 경우 추가 공격을 통해 이어갈수 있음
 */
UCLASS(meta = (DisplayName = "ComboTiming"))
class NEWRPG_API UAnimNotify_ComboTiming : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool bComboTiming;

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
