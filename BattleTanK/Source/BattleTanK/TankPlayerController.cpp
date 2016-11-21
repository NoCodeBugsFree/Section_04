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

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // has a "side-effect". is going to linetrace 
	{
		UE_LOG(LogTemp, Error, TEXT("HitLocation = %s"), *HitLocation.ToString());
		// TODO tell controller tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(2.f, 3.f, 4.f);
	return true;
}

// get world location of linetrace through crosshair, true if it hits the landscape
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


