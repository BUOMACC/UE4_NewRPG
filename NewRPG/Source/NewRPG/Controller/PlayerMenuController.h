// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerMenuController.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API APlayerMenuController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuClass;
	class UUserWidget* MainMenuWidget;
};
