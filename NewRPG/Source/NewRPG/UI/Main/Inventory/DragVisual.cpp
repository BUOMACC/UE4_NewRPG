// Fill out your copyright notice in the Description page of Project Settings.


#include "DragVisual.h"
#include "Components/Image.h"


void UDragVisual::SetVisual(UTexture2D* Texture)
{
	if (Texture)
	{
		// Image Change & Show Image
		Img_Visual->SetBrushFromTexture(Texture, false);
		Img_Visual->SetOpacity(1.f);
	}
	else
	{
		// Image Change & Hide Image
		Img_Visual->SetBrushFromTexture(nullptr);
		Img_Visual->SetOpacity(0.f);
	}
}