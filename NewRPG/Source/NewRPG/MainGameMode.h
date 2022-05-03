// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMainGameMode();

protected:
	virtual void BeginPlay() override;
	void GameClear();
	void GameOver();

	// * DamageText
protected:
	UPROPERTY(EditAnywhere, Category = "Pool")
	TSubclassOf<class ADamageText> DamageTextClass;

	UPROPERTY(EditAnywhere, Category = "Pool")
	int32 PoolCount;

public:
	TQueue<class ADamageText*> Pool;

public:
	UFUNCTION(BlueprintCallable)
	ADamageText* SpawnDamageText(FVector SpawnLoc, float DamageAmount, bool bIsCritical);
};
