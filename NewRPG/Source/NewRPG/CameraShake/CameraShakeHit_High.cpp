// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeHit_High.h"


UCameraShakeHit_High::UCameraShakeHit_High()
{
	OscillationDuration = 0.25f;

	LocOscillation.Y.Amplitude = 12.f;
	LocOscillation.Y.Frequency = 30.f;

	LocOscillation.Z.Amplitude = 12.f;
	LocOscillation.Z.Frequency = 30.f;
}