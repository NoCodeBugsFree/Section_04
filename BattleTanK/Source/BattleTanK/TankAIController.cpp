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

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// fire if ready with limitations
	ControlledTank->Fire();
}
