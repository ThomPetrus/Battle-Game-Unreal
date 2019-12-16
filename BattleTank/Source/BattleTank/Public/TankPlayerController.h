// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

private:
	UPROPERTY(EditDefaultsOnly)
		float ReticleXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float ReticleYLocation = 0.33333;

	// 10km - 10*100cm*1000
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	// Moves barrel to where crosshair intersects world - will need raycasting
	void AimTowardsCrosshair();

	// Returns bool if hit landscape, and modifies an out parameter
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
	// Getting the direction using deprojection method, takes in out parameter
	bool GetCameraDirection(FVector2D ScreenLocation, FVector& CameraDirection) const;

	// Line trace
	bool GetLookVectorHitLocation(FVector CameraDirection, FVector& HitLocation) const;

};
