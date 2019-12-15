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
	UFUNCTION(BluePrintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons - 30kg tank at 1g acceleration
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDrivingForce = 4000000;
};
