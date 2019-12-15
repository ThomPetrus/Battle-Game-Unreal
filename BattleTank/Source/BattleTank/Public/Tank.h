// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankTrack;
class AProjectile;



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	

	UFUNCTION(BluePrintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BluePrintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BluePrintCallable, Category = Setup)
		void SetTrackReference(UTankTrack* TankTrackToSet);

	// TODO - find sensible default
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTimeInSeconds = 3;

	UFUNCTION(BluePrintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;

	void AimAt(FVector HitLocation);

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	double LastFireTime = 0;
};
