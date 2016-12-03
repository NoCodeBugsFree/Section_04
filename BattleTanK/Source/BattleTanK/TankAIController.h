// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
*
*/

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	ATankAIController();


protected:



private:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 80000.f;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UPROPERTY()
	UTankAimingComponent* TankAimingComponent;

};