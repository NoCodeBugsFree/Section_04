// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank && TankAimingComponent)) { return; }

	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim towards the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if aim or locked
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(GetPawn());
		if (!ensure(PossessedTank)) { return; }

		// subscribe our local method to the tank's death event
		// checked this in BeginPlay - valid !!!
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{	
	// Clear Delegates
	if (!ensure(GetPawn())) { return; } // TODO remove ensure if work correctly

	ATank* PossessedTank = Cast<ATank>(GetPawn());
	if (PossessedTank)
	{
		PossessedTank->OnTankDeath.Clear();
		// Call this function to detach safely pawn from its controller, 
		// knowing that we will be destroyed soon
		PossessedTank->DetachFromControllerPendingDestroy();
	}
}