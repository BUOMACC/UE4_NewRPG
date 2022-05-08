// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeHit_Medium.h"


UCameraShakeHit_Medium::UCameraShakeHit_Medium()
{
	OscillationDuration = 0.25f;

	LocOscillation.Y.Amplitude = 7.f;
	LocOscillation.Y.Frequency = 30.f;

	LocOscillation.Z.Amplitude = 7.f;
	LocOscillation.Z.Frequency = 30.f;
}