// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATankAIController();
	

protected:

	
	
private:

	/**  How close can AI tank get  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 3100.f;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
};
