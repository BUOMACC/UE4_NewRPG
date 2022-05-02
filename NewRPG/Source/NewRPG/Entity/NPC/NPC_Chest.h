// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/NPC/NPCBase.h"
#include "NPC_Chest.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API ANPC_Chest : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPC_Chest();

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SMesh_Body;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SMesh_Top;

	virtual void Interact() override;
};
