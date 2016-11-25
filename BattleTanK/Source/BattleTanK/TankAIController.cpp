// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankAIController.h"
#include "Tank.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// TODO move towards the player

		// aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire if ready
		ControlledTank->Fire(); // TODO don't fire every frame
	}
}
