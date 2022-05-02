// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UMessageBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Ok->OnClicked.AddDynamic(this, &UMessageBox::OnClick_Ok);
	Btn_Cancel->OnClicked.AddDynamic(this, &UMessageBox::OnClick_Cancel);
}


void UMessageBox::SetMessage(FText Title, FText Desc, bool HideCancelButton)
{
	Text_Title->SetText(Title);
	Text_Desc->SetText(Desc);

	if (HideCancelButton)
	{
		Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Btn_Cancel->SetVisibility(ESlateVisibility::Visible);
	}
}


void UMessageBox::OnClick_Ok()
{
	RemoveFromParent();
	if (OnOkButtonSelected.IsBound())
	{
		OnOkButtonSelected.Execute();
		OnOkButtonSelected.Unbind();
		OnCancelButtonSelected.Unbind();
	}
}


void UMessageBox::OnClick_Cancel()
{
	RemoveFromParent();
	if (OnCancelButtonSelected.IsBound())
	{
		OnCancelButtonSelected.Execute();
		OnOkButtonSelected.Unbind();
		OnCancelButtonSelected.Unbind();
	}
}