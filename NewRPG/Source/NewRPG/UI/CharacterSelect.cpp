// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelect.h"
#include "Controller/PlayerMenuController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MenuGameMode.h"


void UCharacterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_CharacterName->TextDelegate.BindUFunction(this, TEXT("UpdateCharacterNameText"));
	Text_CharacterDesc->TextDelegate.BindUFunction(this, TEXT("UpdateCharacterDescText"));

	Btn_Next->OnClicked.AddDynamic(this, &UCharacterSelect::OnClick_Next);
}


void UCharacterSelect::OnClick_Next()
{
	APlayerMenuController* PC = Cast<APlayerMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenLoadingScreen(TEXT("Village"), 3.0f);
	}
}


FText UCharacterSelect::UpdateCharacterNameText()
{
	AMenuGameMode* GM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		return GM->GetSelectedCharacterName();
	}
	return FText::FromString(TEXT(""));
}


FText UCharacterSelect::UpdateCharacterDescText()
{
	AMenuGameMode* GM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		return GM->GetSelectedCharacterDesc();
	}
	return FText::FromString(TEXT(""));
}