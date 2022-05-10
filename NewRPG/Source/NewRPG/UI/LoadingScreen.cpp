// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreen.h"
#include "Kismet/GameplayStatics.h"


void ULoadingScreen::StartLoading(FName LevelName, float Time)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([=]()
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, false);
	}), Time, false);
}