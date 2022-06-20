// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Entity/InteractActor.h"
#include "NPCBase.generated.h"

UCLASS()
class NEWRPG_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(EditAnywhere)
	FString NPCName;
};
