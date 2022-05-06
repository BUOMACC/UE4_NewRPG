// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "Entity/Player/BasePlayer.h"
#include "Engine/DataTable.h"
#include "GameData.h"


AMenuGameMode::AMenuGameMode()
{
	CharacterIndex = 0;
}


void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	// * 캐릭터 정보저장
	if (CharacterTable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character DataTable is not set!"));
		return;
	}

	TArray<FName> RowNames = CharacterTable->GetRowNames();
	for (const FName& CurrName : RowNames)
	{
		FCharacterDataRow* CharacterRow = CharacterTable->FindRow<FCharacterDataRow>(CurrName, TEXT(""));
		CharacterNames.Add(CharacterRow->SelectMenuName);
		CharacterDescriptions.Add(CharacterRow->SelectMenuDesc);
		CharacterClasses.Add(CharacterRow->PreviewClass);

	}

	// * 캐릭터 소환
	for (int i = 0; i < CharacterClasses.Num(); i++)
	{
		ABasePlayer* SpawnedCharacter = GetWorld()->SpawnActor<ABasePlayer>(CharacterClasses[i], SpawnPoint);
		SpawnedCharacter->SetActorHiddenInGame(true);
		if (SpawnedCharacter)
		{
			Characters.Add(SpawnedCharacter);
		}
	}

	// 기본선택 캐릭터 보여주기
	if (Characters.Num() != 0)
	{
		Characters[CharacterIndex]->SetActorHiddenInGame(false);
	}
}


void AMenuGameMode::SelectCharacter(int32 NewIndex)
{
	// 선택한 캐릭터 표시
	if (Characters.Num() != 0 && CharacterIndex != NewIndex)
	{
		Characters[CharacterIndex]->SetActorHiddenInGame(true);
		Characters[NewIndex]->SetActorHiddenInGame(false);
		CharacterIndex = NewIndex;

		// GameData에도 선택한 캐릭터 인덱스 반영
		UGameData* Data = Cast<UGameData>(GetGameInstance());
		Data->CharacterIndex = CharacterIndex;
	}
}


FText AMenuGameMode::GetSelectedCharacterName()
{
	if (CharacterNames.Num() <= 0 || CharacterIndex >= CharacterDescriptions.Num())
		return FText::FromString("Unknown");
	return CharacterNames[CharacterIndex];
}


FText AMenuGameMode::GetSelectedCharacterDesc()
{
	if (CharacterDescriptions.Num() <= 0 || CharacterIndex >= CharacterDescriptions.Num())
		return FText::FromString("Setting Description.");
	return CharacterDescriptions[CharacterIndex];
}