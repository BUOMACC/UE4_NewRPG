// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Controller/PlayerGameController.h"
#include "Kismet/GameplayStatics.h"


void UDungeonMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Close->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_CloseButton);
	Btn_Stage1->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_Stage1);
	Btn_Start->OnClicked.AddDynamic(this, &UDungeonMenu::OnClick_Start);
}


void UDungeonMenu::OnClick_CloseButton()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	RemoveFromParent();
}


void UDungeonMenu::OnClick_Stage1()
{
	ImageSwitcher->SetActiveWidgetIndex(0);
	SelectStage = 0;
}


void UDungeonMenu::OnClick_Start()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC == nullptr) return;

	PC->AddUIStack(-1);
	switch (SelectStage)
	{
	case 0:
		PC->OpenLoadingScreen(TEXT("StageGideon"), 3.0f);
		break;
	}
}