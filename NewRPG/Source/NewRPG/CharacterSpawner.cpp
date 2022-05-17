// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSpawner.h"
#include "Components/SphereComponent.h"
#include "Controller/PlayerGameController.h"
#include "Entity/Player/BasePlayer.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"


ACharacterSpawner::ACharacterSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// * GameData의 CharacterIndex에 따라 캐릭터 소환
	UGameData* Data = Cast<UGameData>(GetGameInstance());
	if (Data->CharacterIndex < Characters.Num())
	{
		// 생성위치 설정
		FTransform SpawnTrans;
		SpawnTrans.SetLocation(GetActorLocation());
		SpawnTrans.SetRotation(FRotator(0, GetActorRotation().Yaw, 0).Quaternion());

		// 캐릭터 생성
		APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		ABasePlayer* Character = GetWorld()->SpawnActor<ABasePlayer>(Characters[Data->CharacterIndex], SpawnTrans);

		
		if (Character)
		{
			PC->Possess(Character);
		}
		Destroy();
	}
}
