// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity/InteractActor.h"
#include "NPC_Chest.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API ANPC_Chest : public AActor, public IInteractActor
{
	GENERATED_BODY()
	
public:
	ANPC_Chest();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SMesh_Body;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SMesh_Top;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(EditAnywhere)
	FString NPCName;
};
