// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NewRPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API ANewRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANewRPGGameModeBase();

protected:
	virtual void BeginPlay() override;


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
