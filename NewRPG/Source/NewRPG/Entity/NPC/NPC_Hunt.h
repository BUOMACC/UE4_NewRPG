// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/NPC/NPCBase.h"
#include "NPC_Hunt.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API ANPC_Hunt : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPC_Hunt();

protected:
	virtual void Interact() override;
};
