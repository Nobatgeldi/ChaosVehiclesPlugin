// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "TrackedVehicleAnimationInstance.generated.h"

class UChaosTrackedVehicleMovementComponent;
/**
 * 
 */
struct FWheelAnimationData
{
	FName BoneName;
	FRotator RotOffset;
	FVector LocOffset;
};


/** Proxy override for this UAnimInstance-derived class */
USTRUCT()
	struct CHAOSVEHICLES_API FVehicleAnimationInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

		FVehicleAnimationInstanceProxy()
		: FAnimInstanceProxy()
		, WheelSpokeCount(0)
		, MaxAngularVelocity(256.f)
		, ShutterSpeed(30.f)
		, StageCoachBlend(730.f)
	{
	}

	FVehicleAnimationInstanceProxy(UAnimInstance* Instance)
		: FAnimInstanceProxy(Instance)
		, WheelSpokeCount(0)
		, MaxAngularVelocity(256.f)
		, ShutterSpeed(30.f)
		, StageCoachBlend(730.f)
	{
	}

public:

	void SetTrackedVehicleComponent(const UChaosTrackedVehicleMovementComponent* InWheeledVehicleComponent);

	/** FAnimInstanceProxy interface begin*/
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	/** FAnimInstanceProxy interface end*/

	const TArray<FWheelAnimationData>& GetWheelAnimData() const
	{
		return WheelInstances;
	}

	void SetStageCoachEffectParams(int InWheelSpokeCount, float InMaxAngularVelocity, float InShutterSpeed, float InStageCoachBlend)
	{
		WheelSpokeCount = InWheelSpokeCount;
		MaxAngularVelocity = InMaxAngularVelocity;
		ShutterSpeed = InShutterSpeed;
		StageCoachBlend = InStageCoachBlend;
	}

private:
	TArray<FWheelAnimationData> WheelInstances;

	int WheelSpokeCount;			// Number of spokes visible on wheel
	float MaxAngularVelocity;		// Wheel max rotation speed in degrees/second
	float ShutterSpeed;				// Camera shutter speed in frames/second
	float StageCoachBlend;			// Blend effect degrees/second

};

UCLASS(transient)
	class CHAOSVEHICLES_API UTrackedVehicleAnimationInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

		/** Makes a montage jump to the end of a named section. */
		UFUNCTION(BlueprintCallable, Category = "Animation")
		class AWheeledVehiclePawn* GetVehicle();

public:
	TArray<TArray<FWheelAnimationData>> WheelData;

public:
	void SetTrackedVehicleComponent(const UChaosTrackedVehicleMovementComponent* InWheeledVehicleComponent)
	{
		WheeledVehicleComponent = InWheeledVehicleComponent;
		AnimInstanceProxy.SetTrackedVehicleComponent(InWheeledVehicleComponent);
	}
	
	const UChaosTrackedVehicleMovementComponent* GetTrackedVehicleComponent() const
	{
		return WheeledVehicleComponent;
	}

private:
	/** UAnimInstance interface begin*/
	virtual void NativeInitializeAnimation() override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;
	/** UAnimInstance interface end*/

	FVehicleAnimationInstanceProxy AnimInstanceProxy;

	UPROPERTY(transient)
	TObjectPtr<const UChaosTrackedVehicleMovementComponent> WheeledVehicleComponent;
};


