// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelect.h"
#include "Components/TextBlock.h"
#include "MenuGameMode.h"


void UCharacterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_CharacterName->TextDelegate.BindUFunction(this, TEXT("UpdateCharacterNameText"));
	Text_CharacterDesc->TextDelegate.BindUFunction(this, TEXT("UpdateCharacterDescText"));
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