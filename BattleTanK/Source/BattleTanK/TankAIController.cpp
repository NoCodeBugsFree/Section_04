// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

ATank* ATankAIController::GetPlayerTank() const
{
	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController && GetPawn())
		{
			ATank* Tank = Cast<ATank>(PlayerController->GetPawn());
			return Tank;
		}
	}
	return nullptr;
}

ATank* ATankAIController::GetControlledTank() const
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
