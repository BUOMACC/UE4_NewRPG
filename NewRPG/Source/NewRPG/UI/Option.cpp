// Fill out your copyright notice in the Description page of Project Settings.


#include "Option.h"
#include "Controller/PlayerGameController.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"


void UOption::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DropDown_Shadow->OnSelectionChanged.AddDynamic(this, &UOption::OnSelected_Shadow);
	DropDown_AntiAliasing->OnSelectionChanged.AddDynamic(this, &UOption::OnSelected_AntiAliasing);
	DropDown_PostProcessing->OnSelectionChanged.AddDynamic(this, &UOption::OnSelected_PostProcessing);

	Btn_Close->OnClicked.AddDynamic(this, &UOption::OnClick_CloseButton);
}


void UOption::NativeConstruct()
{
	Super::NativeConstruct();

	// DropDown 정보들 초기화
	UGameUserSettings* Setting = GEngine->GetGameUserSettings();
	DropDown_Shadow->SetSelectedIndex(Setting->GetShadowQuality());
	DropDown_AntiAliasing->SetSelectedIndex(Setting->GetAntiAliasingQuality());
	DropDown_PostProcessing->SetSelectedIndex(Setting->GetPostProcessingQuality());
}


void UOption::OnSelected_Shadow(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Quality = ConvertQuality(SelectedItem);
	UGameUserSettings* Setting = GEngine->GetGameUserSettings();
	Setting->SetShadowQuality(Quality);
	Setting->ApplySettings(true);
}


void UOption::OnSelected_AntiAliasing(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Quality = ConvertQuality(SelectedItem);
	UGameUserSettings* Setting = GEngine->GetGameUserSettings();
	Setting->SetAntiAliasingQuality(Quality);
	Setting->ApplySettings(true);
}


void UOption::OnSelected_PostProcessing(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Quality = ConvertQuality(SelectedItem);
	UGameUserSettings* Setting = GEngine->GetGameUserSettings();
	Setting->SetPostProcessingQuality(Quality);
	Setting->ApplySettings(true);
}


void UOption::OnClick_CloseButton()
{
	APlayerGameController* PC = Cast<APlayerGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddUIStack(-1);
	}
	RemoveFromParent();
}


int32 UOption::ConvertQuality(FString& In)
{
	if (In == FString(TEXT("낮음")))
	{
		return 0;
	}
	else if (In == FString(TEXT("중간")))
	{
		return 1;
	}
	else if (In == FString(TEXT("높음")))
	{
		return 2;
	}
	else if (In == FString(TEXT("매우높음")))
	{
		return 3;
	}
	return 3;
}