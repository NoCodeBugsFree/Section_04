// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	// get world location if linetrace through crosshair
		// if it hits the landscape
			// tell controller tank to aim at this point
}

ATank* ATankPlayerController::GetControlledTank() const
{
	if (GetPawn())
	{
		return Cast<ATank>(GetPawn());
	}
	else
	{
		return nullptr;
	}
}


