// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeHit_Low.h"


UCameraShakeHit_Low::UCameraShakeHit_Low()
{
	OscillationDuration = 0.25f;

	LocOscillation.Y.Amplitude = 4.f;
	LocOscillation.Y.Frequency = 30.f;

	LocOscillation.Z.Amplitude = 4.f;
	LocOscillation.Z.Frequency = 30.f;
}