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

	// 캐릭터의 정보를 담고있는 Table
	UPROPERTY(EditAnywhere, Category = "Character Data")
	class UDataTable* CharacterTable;

	UPROPERTY(EditAnywhere, Category = "Character Data")
	FTransform SpawnPoint;
	
private:
	// 생성된 캐릭터액터를 저장
	UPROPERTY()
	TArray<class ABasePlayer*> Characters;

	// 캐릭터 정보들
	UPROPERTY()
	TArray<FText> CharacterNames;

	UPROPERTY()
	TArray<FText> CharacterDescriptions;

	UPROPERTY()
	TArray<TSubclassOf<class ABasePlayer>> CharacterClasses;
};
