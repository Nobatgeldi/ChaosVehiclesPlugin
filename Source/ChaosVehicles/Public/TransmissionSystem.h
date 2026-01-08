// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FSimpleTrackedVehicle.h"
#include "Containers/Array.h"
#include "Math/UnrealMathSSE.h"
#include "VehicleSystemTemplate.h"
#include "VehicleUtility.h"

#if VEHICLE_DEBUGGING_ENABLED
UE_DISABLE_OPTIMIZATION_SHIP
#endif

/**
 * Typical gear ratios: Reverse −4.181, 1st 3.818, 2nd 2.294, 3rd 1.500, 4th 1.133, 5th 0.911 
 * Source: Georg Rill. Road Vehicle Dynamics: Fundamentals and Modeling (Ground Vehicle Engineering Series) (p. 121). CRC Press.
 * 
 *	#todo: Add clutch option
 *	#todo: Proper defaults
 */
namespace ChaosTracked
{

	struct FTrackedDifferentialConfig : public Chaos::FSimpleDifferentialConfig
	{
		FTrackedDifferentialConfig()
			: FSimpleDifferentialConfig()
			, LeftTrackTorqueMultiplier(1.0f)
			, RightTrackTorqueMultiplier(1.0f)
		{
		}

		float LeftTrackTorqueMultiplier;
		float RightTrackTorqueMultiplier;
	};
	

	class FTrackedDifferentialSim : public Chaos::FSimpleDifferentialSim
	{
	public:
		FTrackedDifferentialSim(const FTrackedDifferentialConfig* SetupIn)
			: FSimpleDifferentialSim(SetupIn)
		{
		}

		const FTrackedDifferentialConfig& TrackedSetup() const
		{
			return static_cast<const FTrackedDifferentialConfig&>(Setup());
		}
	};
	
	/** 
	 * Configuration for tracked vehicle transmission.
	 * Inherits base transmission settings and allows for tracked-specific overrides.
	 */
	struct  FTrackedTransmissionConfig : public Chaos::FSimpleTransmissionConfig
	{
		FTrackedTransmissionConfig()
			: FSimpleTransmissionConfig()
		{
		}
		
		// Add tracked specific config here (e.g. PivotTurnRatio)
	};
	/**
	 * Transmission simulation specialized for tracked vehicles (Tanks, Bulldozers, etc.)
	 */
	class  FTrackedTransmissionSim : public Chaos::FSimpleTransmissionSim
	{
	public:
		FTrackedTransmissionSim(const FTrackedTransmissionConfig* SetupIn)
			: FSimpleTransmissionSim(SetupIn)
		{
		}

		/** 
		 * Access to the specific tracked configuration 
		 */
		const FTrackedTransmissionConfig& TrackedSetup() const
		{
			return static_cast<const FTrackedTransmissionConfig&>(Setup());
		}
	};
	
}
