// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) 
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

// No need for super as were changing functionality - Dynamic binding
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntentMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntentTurnRight(RightThrow);
}

void UTankMovementComponent::IntentMoveForward(float Throw) 
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentTurnRight(float Throw) 
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

