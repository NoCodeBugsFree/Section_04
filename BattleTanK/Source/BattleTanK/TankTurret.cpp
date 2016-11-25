// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Rotate the turret the right amount this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));
}
