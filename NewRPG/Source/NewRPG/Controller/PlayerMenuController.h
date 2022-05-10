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

public:
	void OpenLoadingScreen(FName LevelName, float WaitTime);

protected:
	// ���� �޴��� ǥ���� ȭ��
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY()
	class UUserWidget* MainMenuWidget;

	// �ε��� ���� ȭ��
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class ULoadingScreen> LoadingClass;

	UPROPERTY()
	class ULoadingScreen* LoadingScreen;
};
