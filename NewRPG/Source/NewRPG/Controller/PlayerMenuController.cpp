// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMenuController.h"
#include "UI/LoadingScreen.h"


void APlayerMenuController::BeginPlay()
{
	Super::BeginPlay();

	// InputMode Setting
	FInputModeUIOnly InputMode;
	SetShowMouseCursor(true);
	SetInputMode(InputMode);

	// MainMenu Widget 积己
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuClass);
		MainMenuWidget->AddToViewport();
	}

	// LoadingScreen捞 绝促搁 积己
	if (LoadingClass)
	{
		LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingClass);
	}
}


void APlayerMenuController::OpenLoadingScreen(FName LevelName, float WaitTime)
{
	if (LoadingScreen == nullptr) return;
	LoadingScreen->AddToViewport();
	LoadingScreen->StartLoading(LevelName, WaitTime);
}