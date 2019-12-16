// Copyright Thomas Van De Crommenacker 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Aming states
UENUM()
enum class EFiringStates : uint8
	{
		Reloading, 
		Aiming, 
		Locked
	};

// Forward Declaration
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);


protected:
	UPROPERTY(BlueprintReadOnly, Category = "States")
		EFiringStates FiringState = EFiringStates::Locked;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrel(FVector AimDirection);
};
