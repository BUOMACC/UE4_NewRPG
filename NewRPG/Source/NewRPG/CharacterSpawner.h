// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "CharacterSpawner.generated.h"

UCLASS()
class NEWRPG_API ACharacterSpawner : public ADefaultPawn
{
	GENERATED_BODY()

public:
	ACharacterSpawner();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ABasePlayer>> Characters;
};
