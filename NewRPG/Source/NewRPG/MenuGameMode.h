// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/CharacterDataRow.h"
#include "GameFramework/GameMode.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEWRPG_API AMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMenuGameMode();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SelectCharacter(int32 NewIndex);

	UFUNCTION(BlueprintPure)
	FText GetSelectedCharacterName();

	UFUNCTION(BlueprintPure)
	FText GetSelectedCharacterDesc();

protected:
	int32 CharacterIndex;

	// ĳ������ ������ ����ִ� Table
	UPROPERTY(EditAnywhere, Category = "Character Data")
	class UDataTable* CharacterTable;

	UPROPERTY(EditAnywhere, Category = "Character Data")
	FTransform SpawnPoint;
	
private:
	// ������ ĳ���;��͸� ����
	UPROPERTY()
	TArray<class ABasePlayer*> Characters;

	// ĳ���� ������
	UPROPERTY()
	TArray<FText> CharacterNames;

	UPROPERTY()
	TArray<FText> CharacterDescriptions;

	UPROPERTY()
	TArray<TSubclassOf<class ABasePlayer>> CharacterClasses;
};
