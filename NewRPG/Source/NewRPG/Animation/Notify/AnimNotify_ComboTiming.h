// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ComboTiming.generated.h"

/**
 * ���� �޺��� �̾�� ���� �޺����� ���¸� �����ϴ� Notify
 * ComboTiming ������ true�� ��� �߰� ������ ���� �̾�� ����
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
