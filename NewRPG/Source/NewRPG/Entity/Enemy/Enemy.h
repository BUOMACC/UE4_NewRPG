// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Entity.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API AEnemy : public AEntity
{
	GENERATED_BODY()
	
public:
	AEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Dead(AActor* Killer) override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	// 적의 정보를 담고있는 Table
	UPROPERTY(EditAnywhere, Category = "Enemy Data")
	class UDataTable* EnemyTable;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthBarWidget;

private:
	void SettingStatFromTable();
	void SettingHealthBar();
};
