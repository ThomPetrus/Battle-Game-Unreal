// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "TankPlayerController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
		float ReticleXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float ReticleYLocation = 0.33333;

	// 10km - 10*100cm*1000
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	// For finding the instance of the tank being controlled.
	ATank* GetControlledTank() const;
	
	// Moves barrel to where crosshair intersects world - will need raycasting
	void AimTowardsCrosshair();

	// Returns bool if hit landscape, and modifies an out parameter
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
	// Getting the direction using deprojection method, takes in out parameter
	bool GetCameraDirection(FVector2D ScreenLocation, FVector& CameraDirection) const;

	// Line trace
	bool GetLookVectorHitLocation(FVector CameraDirection, FVector& HitLocation) const;

};
