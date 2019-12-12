// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFrameWork/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a Tank"));
	}
	else
	{

	}
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) 
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto P1Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!P1Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find P1 controller"));
		return nullptr;
	}
	else
	{
		return Cast<ATank>(P1Pawn);
	}
}
