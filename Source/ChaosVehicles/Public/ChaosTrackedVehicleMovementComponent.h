// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleMovementComponent.h"

#include "ChaosTrackedVehicleMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHAOSVEHICLES_API UChaosTrackedVehicleMovementComponent : public UChaosVehicleMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UChaosTrackedVehicleMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
