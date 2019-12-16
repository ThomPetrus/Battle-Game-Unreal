// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AimingComponent not found by Player Controller at begin play."));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}
	// Out parameter
	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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
		GetLookVectorHitLocation(CameraDirection, OutHitLocation);

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
	//OutHitLocation = FVector(0);
	return false;
}