// Fill out your copyright notice in the Description page of Project Settings.


#include "NameTag.h"
#include "Components/TextBlock.h"


void UNameTag::SetNameTag(FString& Name)
{
	FText NameText = FText::FromString(Name);
	Text_NameTag->SetText(NameText);
}