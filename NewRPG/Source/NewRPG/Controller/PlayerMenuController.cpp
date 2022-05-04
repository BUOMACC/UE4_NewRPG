// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMenuController.h"
#include "Blueprint/UserWidget.h"


void APlayerMenuController::BeginPlay()
{
	Super::BeginPlay();

	// InputMode Setting
	FInputModeUIOnly InputMode;
	SetShowMouseCursor(true);
	SetInputMode(InputMode);

	// MainMenu Widget »ý¼º
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuClass);
		MainMenuWidget->AddToViewport();
	}
}