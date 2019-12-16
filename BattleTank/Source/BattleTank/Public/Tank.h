// Copyright Thomas Van De Crommenacker 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTrack;
class AProjectile;



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	void AimAt(FVector HitLocation);

	// TODO - find sensible default
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3;

	UFUNCTION(BluePrintCallable, Category = "Firing")
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	double LastFireTime = 0;
};
