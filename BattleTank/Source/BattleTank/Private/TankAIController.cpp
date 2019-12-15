// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFrameWork/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a Tank"));
	}
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a Tank"));
	}
	else
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}

