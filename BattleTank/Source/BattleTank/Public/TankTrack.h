// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BluePrintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UFUNCTION(BluePrintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track in Newtons - 30kg tank at 1g acceleration
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDrivingForce = 40000000;

private:

	TArray<class ASprungWheel*> GetWheels() const;

	virtual void BeginPlay() override;

	void DriveTrack(float CurrentThrottle);
};
