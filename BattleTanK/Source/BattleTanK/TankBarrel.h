// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Elevate(float DegreesPerSecond);

protected:



private:
	
	/** Sensible Default  */
	UPROPERTY(EditAnywhere, Category = "AAA")
	float MaxDegreesPerSecond = 20.f;

	/** Sensible Default  */
	UPROPERTY(EditAnywhere, Category = "AAA")
	float MaxElevationDegrees = 35.f;

	/** Sensible Default  */
	UPROPERTY(EditAnywhere, Category = "AAA")
	float MinElevationDegrees = 0.f;


	
};
