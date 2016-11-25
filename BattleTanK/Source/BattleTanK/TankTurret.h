// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Rotate(float RelativeSpeed);

protected:



private:
	
	/** Sensible Default  */
	UPROPERTY(EditAnywhere, Category = "AAA")
	float MaxDegreesPerSecond = 5.f;
	
};
