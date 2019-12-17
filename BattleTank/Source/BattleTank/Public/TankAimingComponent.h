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
		Locked, 
		OutOfAmmo
	};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BluePrintCallable, Category = "Firing")
		void Fire();

	EFiringStates GetFiringState() const;


	UFUNCTION(BluePrintCallable, Category = "Firing")
		int GetAmmoRemaining() const;


	UPROPERTY(BlueprintReadOnly, Category = "States")
		EFiringStates FiringState = EFiringStates::Locked;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3;

	FVector AimDirection;

	// TODO REFACTOR Public / private / protected

	// Sets default values for this component's properties
	UTankAimingComponent();


	void MoveBarrel(FVector AimDirection);
	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int Ammo = 30;
};
