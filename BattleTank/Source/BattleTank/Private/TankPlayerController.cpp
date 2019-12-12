// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a Tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) 
	{
		return;
	}
	// Out parameter
	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find crosshair position on screen, more out parameters
	int32 PosX, PosY;
	GetViewportSize(PosX, PosY);

	// then calculate a FVector2D
	auto ScreenLocation = FVector2D(PosX * ReticleXLocation, PosY * ReticleYLocation);
	
	FVector CameraDirection;
	if (GetCameraDirection(ScreenLocation, CameraDirection)) {
		
		// line trace, and see what we hit, w/ max range
		if (GetLookVectorHitLocation(CameraDirection, OutHitLocation)) 
		{

		}

	}

	return true;
}

bool ATankPlayerController::GetCameraDirection(FVector2D ScreenLocation, FVector& CameraDirection) const
{
	// De-project the screen pos of the reticle to a world position, out parameter again.
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, CameraDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector CameraDirection, FVector& OutHitLocation) const
{
	// ye ol line tracerino
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (CameraDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}