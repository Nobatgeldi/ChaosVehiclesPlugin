# API Reference

This document provides detailed API reference for the ChaosVehiclesPlugin.

## Table of Contents
1. [Core Classes](#core-classes)
2. [Movement Components](#movement-components)
3. [Wheel Classes](#wheel-classes)
4. [Configuration Structures](#configuration-structures)
5. [Animation Nodes](#animation-nodes)
6. [Debug System](#debug-system)

## Core Classes

### AWheeledVehiclePawn

The base pawn class for wheeled vehicles.

**Header**: `WheeledVehiclePawn.h`

**Description**: Base wheeled vehicle pawn actor that integrates mesh and movement components.

#### Key Components
```cpp
// The main skeletal mesh associated with this Vehicle
USkeletalMeshComponent* Mesh;

// Vehicle simulation component
UChaosVehicleMovementComponent* VehicleMovementComponent;
```

#### Key Methods
```cpp
// Get the vehicle movement component
UChaosVehicleMovementComponent* GetVehicleMovementComponent() const;

// Get the skeletal mesh component
USkeletalMeshComponent* GetMesh() const;

// Display debug information
virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
```

#### Static Names
```cpp
static FName VehicleMeshComponentName;        // "VehicleMesh"
static FName VehicleMovementComponentName;    // "VehicleMovement"
```

#### Usage Example
```cpp
// Creating a custom vehicle pawn
UCLASS()
class AMyVehicle : public AWheeledVehiclePawn
{
    GENERATED_BODY()
    
public:
    AMyVehicle(const FObjectInitializer& ObjectInitializer)
        : Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCustomMovement>(VehicleMovementComponentName))
    {
        // Custom initialization
    }
};
```

---

## Movement Components

### UChaosVehicleMovementComponent

Base class for all Chaos vehicle movement components.

**Header**: `ChaosVehicleMovementComponent.h`

**Description**: Handles vehicle physics simulation, input processing, and replication.

#### Key Properties

**Torque Control**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
FVehicleTorqueControlConfig TorqueControl;
```

**Target Rotation Control**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
FVehicleTargetRotationControlConfig TargetRotationControl;
```

**Stability Control**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
FVehicleStabilizeControlConfig StabilizeControl;
```

**Aerodynamics**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
TArray<FAerofoilConfig> Aerofoils;

UPROPERTY(EditAnywhere, Category = "VehicleSetup")
TArray<FThrusterConfig> Thrusters;
```

#### Key Methods

**Input Control**
```cpp
// Set throttle input [0.0 to 1.0]
void SetThrottleInput(float Throttle);

// Set steering input [-1.0 to 1.0]
void SetSteeringInput(float Steering);

// Set brake input [0.0 to 1.0]
void SetBrakeInput(float Brake);

// Set pitch input [-1.0 to 1.0]
void SetPitchInput(float Pitch);

// Set roll input [-1.0 to 1.0]
void SetRollInput(float Roll);

// Set yaw input [-1.0 to 1.0]
void SetYawInput(float Yaw);

// Set handbrake
void SetHandbrakeInput(bool bHandbrake);
```

**State Queries**
```cpp
// Get forward speed in cm/s
float GetForwardSpeed() const;

// Get forward speed in MPH
float GetForwardSpeedMPH() const;

// Check if vehicle is on ground
bool IsOnGround() const;
```

**Advanced Control**
```cpp
// Enable or disable vehicle simulation
void SetSleeping(bool bEnableSleep);

// Reset the vehicle to a known state
void ResetVehicleState();
```

---

### UChaosWheeledVehicleMovementComponent

Wheeled vehicle implementation with suspension and wheel simulation.

**Header**: `ChaosWheeledVehicleMovementComponent.h`

**Inherits**: `UChaosVehicleMovementComponent`

#### Key Properties

**Wheel Setup**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
TArray<FWheelSetup> WheelSetups;

UPROPERTY(EditAnywhere, Category = "VehicleSetup")
bool bMechanicalSimEnabled;
```

**Engine Configuration**
```cpp
UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
FVehicleEngineConfig EngineSetup;

UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
FVehicleDifferentialConfig DifferentialSetup;

UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
FVehicleTransmissionConfig TransmissionSetup;

UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
FVehicleSteeringConfig SteeringSetup;
```

**Suspension Settings**
```cpp
UPROPERTY(EditAnywhere, Category = "VehicleSetup")
bool bSuspensionEnabled;

UPROPERTY(EditAnywhere, Category = "VehicleSetup")
EVehicleDifferential DifferentialType;
```

#### Key Methods

**Wheel Access**
```cpp
// Get specific wheel by index
UChaosVehicleWheel* GetWheel(int32 WheelIndex) const;

// Get number of wheels
int32 GetNumWheels() const;

// Get wheel status information
void GetWheelStatus(int32 WheelIndex, FWheelStatus& Status) const;
```

**Gear Control**
```cpp
// Set target gear (manual transmission)
void SetTargetGear(int32 GearNum, bool bImmediate);

// Get current gear
int32 GetCurrentGear() const;

// Get target gear
int32 GetTargetGear() const;

// Check if in reverse
bool GetUseAutoGears() const;
```

**Engine State**
```cpp
// Get engine RPM
float GetEngineRPM() const;

// Get engine max RPM
float GetEngineMaxRPM() const;
```

#### Debug Methods
```cpp
// Enable debug mode
void EnableDebug(bool bEnable);

// Set debug page
void SetDebugPage(int32 PageIndex);
```

---

### UChaosTrackedVehicleMovementComponent

Tracked vehicle implementation (experimental).

**Header**: `ChaosTrackedVehicleMovementComponent.h`

**Inherits**: `UChaosVehicleMovementComponent`

**Description**: Movement component for tracked vehicles like tanks or bulldozers.

**Status**: Experimental - API may change

---

## Wheel Classes

### UChaosVehicleWheel

Defines individual wheel configuration and behavior.

**Header**: `ChaosVehicleWheel.h`

#### Key Properties

**Shape Configuration**
```cpp
UPROPERTY(EditDefaultsOnly, Category = "Shape")
UStaticMesh* CollisionMesh;

UPROPERTY(EditDefaultsOnly, Category = "Shape")
float ShapeRadius;

UPROPERTY(EditDefaultsOnly, Category = "Shape")
float ShapeWidth;

UPROPERTY(EditDefaultsOnly, Category = "Shape")
float SimpleShapeRadius;
```

**Suspension Settings**
```cpp
UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionAxis;           // -1 = down, 1 = up

UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionForceOffset;

UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionMaxRaise;       // cm

UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionMaxDrop;        // cm

UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionDampingRatio;   // 0.0 to 1.0

UPROPERTY(EditAnywhere, Category = "Suspension")
float SuspensionNaturalFrequency;  // Hz

UPROPERTY(EditAnywhere, Category = "Suspension")
ESweepShape SweepShape;         // Raycast, Spherecast, Shapecast

UPROPERTY(EditAnywhere, Category = "Suspension")
ESweepType SweepType;           // SimpleSweep, ComplexSweep
```

**Wheel Behavior**
```cpp
UPROPERTY(EditAnywhere, Category = "Wheel")
bool bAffectedByEngine;

UPROPERTY(EditAnywhere, Category = "Wheel")
bool bAffectedByBrake;

UPROPERTY(EditAnywhere, Category = "Wheel")
bool bAffectedByHandbrake;

UPROPERTY(EditAnywhere, Category = "Wheel")
bool bAffectedBySteering;

UPROPERTY(EditAnywhere, Category = "Wheel")
float MaxSteerAngle;            // Degrees

UPROPERTY(EditAnywhere, Category = "Wheel")
float MaxBrakeTorque;           // N⋅m

UPROPERTY(EditAnywhere, Category = "Wheel")
float HandBrakeTorque;          // N⋅m

UPROPERTY(EditAnywhere, Category = "Wheel")
EAxleType AxleType;             // Front, Rear, Undefined
```

**Friction Configuration**
```cpp
UPROPERTY(EditAnywhere, Category = "Friction")
float FrictionForceMultiplier;

UPROPERTY(EditAnywhere, Category = "Friction")
float CorneringStiffness;

UPROPERTY(EditAnywhere, Category = "Friction")
float SideSlipModifier;

UPROPERTY(EditAnywhere, Category = "Friction")
FRuntimeFloatCurve LateralSlipGraph;

UPROPERTY(EditAnywhere, Category = "Friction")
float SlipThreshold;

UPROPERTY(EditAnywhere, Category = "Friction")
float SkidThreshold;
```

**Advanced Settings**
```cpp
UPROPERTY(EditAnywhere, Category = "Wheel")
float ExternalTorque;

UPROPERTY(EditAnywhere, Category = "Wheel")
ETorqueCombineMethod TorqueCombineMethod;
```

#### Key Methods
```cpp
// Get wheel rotation angle in degrees
float GetRotationAngle() const;

// Get wheel rotation angular velocity
float GetRotationAngularVelocity() const;

// Get suspension offset
float GetSuspensionOffset() const;

// Check if wheel is in contact with ground
bool IsInContact() const;
```

---

## Configuration Structures

### FVehicleTorqueControlConfig

Configuration for vehicle torque control system.

```cpp
USTRUCT()
struct FVehicleTorqueControlConfig
{
    // Enable torque control
    UPROPERTY(EditAnywhere, Category = "Setup")
    bool Enabled;
    
    // Yaw torque scaling
    UPROPERTY(EditAnywhere, Category = "Setup")
    float YawTorqueScaling;
    
    // Pitch torque scaling
    UPROPERTY(EditAnywhere, Category = "Setup")
    float PitchTorqueScaling;
    
    // Roll torque scaling
    UPROPERTY(EditAnywhere, Category = "Setup")
    float RollTorqueScaling;
    
    // Rotation damping
    UPROPERTY(EditAnywhere, Category = "Setup")
    float RotationDamping;
};
```

### FWheelStatus

Runtime wheel state information.

```cpp
USTRUCT(BlueprintType)
struct FWheelStatus
{
    // Is wheel in contact with ground
    UPROPERTY(BlueprintReadOnly)
    bool bInContact;
    
    // Contact point in world space
    UPROPERTY(BlueprintReadOnly)
    FVector ContactPoint;
    
    // Hit location
    UPROPERTY(BlueprintReadOnly)
    FVector HitLocation;
    
    // Physical material at contact
    UPROPERTY(BlueprintReadOnly)
    TWeakObjectPtr<UPhysicalMaterial> PhysMaterial;
    
    // Normalized suspension length [0.0 = compressed, 1.0 = extended]
    UPROPERTY(BlueprintReadOnly)
    float NormalizedSuspensionLength;
    
    // Spring force being applied
    UPROPERTY(BlueprintReadOnly)
    float SpringForce;
    
    // Current slip angle
    UPROPERTY(BlueprintReadOnly)
    float SlipAngle;
    
    // Is wheel slipping
    UPROPERTY(BlueprintReadOnly)
    bool bIsSlipping;
    
    // Slip magnitude
    UPROPERTY(BlueprintReadOnly)
    float SlipMagnitude;
    
    // Is wheel skidding
    UPROPERTY(BlueprintReadOnly)
    bool bIsSkidding;
    
    // Skid magnitude
    UPROPERTY(BlueprintReadOnly)
    float SkidMagnitude;
    
    // Drive torque
    UPROPERTY(BlueprintReadOnly)
    float DriveTorque;
    
    // Brake torque
    UPROPERTY(BlueprintReadOnly)
    float BrakeTorque;
};
```

### FVehicleEngineConfig

Engine configuration structure.

```cpp
USTRUCT()
struct FVehicleEngineConfig
{
    // Torque curve vs RPM
    UPROPERTY(EditAnywhere, Category = "Setup")
    FRuntimeFloatCurve TorqueCurve;
    
    // Maximum engine RPM
    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxRPM;
    
    // Moment of inertia
    UPROPERTY(EditAnywhere, Category = "Setup")
    float MOI;
    
    // Damping when throttle is zero and clutch engaged
    UPROPERTY(EditAnywhere, Category = "Setup")
    float DampingRateZeroThrottleClutchEngaged;
    
    // Damping when throttle is zero and clutch disengaged
    UPROPERTY(EditAnywhere, Category = "Setup")
    float DampingRateZeroThrottleClutchDisengaged;
    
    // Damping at full throttle
    UPROPERTY(EditAnywhere, Category = "Setup")
    float DampingRateFullThrottle;
};
```

### FVehicleTransmissionConfig

Transmission configuration structure.

```cpp
USTRUCT()
struct FVehicleTransmissionConfig
{
    // Forward gear ratios
    UPROPERTY(EditAnywhere, Category = "Setup")
    TArray<float> ForwardGearRatios;
    
    // Reverse gear ratio
    UPROPERTY(EditAnywhere, Category = "Setup")
    float ReverseGearRatio;
    
    // Final drive ratio
    UPROPERTY(EditAnywhere, Category = "Setup")
    float FinalRatio;
    
    // Time to change gear (seconds)
    UPROPERTY(EditAnywhere, Category = "Setup")
    float GearChangeTime;
    
    // Transmission efficiency [0.0-1.0]
    UPROPERTY(EditAnywhere, Category = "Setup")
    float TransmissionEfficiency;
};
```

### EVehicleDifferential

Differential type enumeration.

```cpp
UENUM()
enum class EVehicleDifferential : uint8
{
    Undefined,
    AllWheelDrive,
    FrontWheelDrive,
    RearWheelDrive
};
```

### EAxleType

Axle type enumeration.

```cpp
UENUM()
enum class EAxleType : uint8
{
    Undefined,
    Front,
    Rear
};
```

---

## Animation Nodes

### UAnimNode_WheelController

Animation node for wheel rotation and suspension animation.

**Header**: `AnimNode_WheelController.h`

**Description**: Automatically animates wheel rotation and suspension based on vehicle physics.

#### Usage in Animation Blueprint
1. Add "Wheel Controller" node in AnimGraph
2. Configure wheel bone names
3. Connect to output pose

---

### UAnimNode_StageCoachWheelController

Specialized wheel controller for stage coach style wheels.

**Header**: `AnimNode_StageCoachWheelController.h`

**Description**: Similar to WheelController but with additional features for historical vehicle wheels.

---

## Debug System

### Debug Console Commands

Enable debug visualization and information:

```cpp
// Show main debug display
p.Vehicles.ShowDebug 1

// Navigate debug pages
p.Vehicles.NextDebugPage
p.Vehicles.PrevDebugPage

// Show specific visualizations
p.Vehicles.ShowSuspensionRaycasts 1
p.Vehicles.ShowWheelForces 1
p.Vehicles.ShowSuspensionForces 1
p.Vehicles.ShowWheelCollisionNormal 1
p.Vehicles.ShowCOM 1
p.Vehicles.ShowAllForces 1

// Disable specific forces (for debugging)
p.Vehicles.DisableSuspensionForces 1
p.Vehicles.DisableFrictionForces 1
p.Vehicles.DisableRollbarForces 1

// Performance
p.Vehicles.BatchQueries 1
p.Vehicles.EnableMultithreading 1
```

### Debug Pages

| Page | Information Displayed |
|------|----------------------|
| BasicPage | Speed, RPM, gear, steering angle, basic state |
| PerformancePage | Frame times, physics timing, query counts |
| SteeringPage | Steering angles, inputs, wheel states |
| FrictionPage | Friction forces, slip angles, contact info |
| SuspensionPage | Suspension compression, forces, contact points |
| TransmissionPage | Gear ratios, clutch, torque distribution |

### FVehicleDebugParams

Debug configuration structure:

```cpp
struct FVehicleDebugParams
{
    bool ShowCOM;
    bool ShowModelOrigin;
    bool ShowAllForces;
    bool ShowAerofoilForces;
    bool ShowAerofoilSurface;
    bool DisableTorqueControl;
    bool DisableStabilizeControl;
    bool DisableAerodynamics;
    bool DisableAerofoils;
    bool DisableThrusters;
    bool BatchQueries;
    bool CacheTraceOverlap;
    float ForceDebugScaling;
    bool DisableVehicleSleep;
    bool EnableMultithreading;
    float SetMaxMPH;
};
```

---

## Blueprint Function Library

While not explicitly a separate class in the current implementation, many vehicle functions are exposed to Blueprint:

### Blueprint Callable Functions

**Movement Control**
- `SetThrottleInput(float Throttle)`
- `SetSteeringInput(float Steering)`
- `SetBrakeInput(float Brake)`
- `SetHandbrakeInput(bool bHandbrake)`

**State Queries**
- `GetForwardSpeed() -> float`
- `GetCurrentGear() -> int32`
- `GetEngineRPM() -> float`
- `GetWheelStatus(int32 WheelIndex) -> FWheelStatus`

**Gear Control**
- `SetTargetGear(int32 GearNum, bool bImmediate)`
- `GetUseAutoGears() -> bool`
- `SetUseAutoGears(bool bAutoGears)`

---

## Examples

### C++ Example: Custom Vehicle Initialization

```cpp
#include "WheeledVehiclePawn.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ChaosVehicleWheel.h"

void AMyVehicle::BeginPlay()
{
    Super::BeginPlay();
    
    if (UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent()))
    {
        // Configure for performance car
        VehicleMovement->EngineSetup.MaxRPM = 8000.0f;
        VehicleMovement->DifferentialType = EVehicleDifferential::RearWheelDrive;
        
        // Iterate through wheels
        for (int32 i = 0; i < VehicleMovement->GetNumWheels(); ++i)
        {
            if (UChaosVehicleWheel* Wheel = VehicleMovement->GetWheel(i))
            {
                // Increase grip for all wheels
                Wheel->FrictionForceMultiplier = 3.5f;
            }
        }
    }
}
```

### Blueprint Example: Get Wheel Contact Info

```
Event Tick
├─ Get Vehicle Movement Component
├─ For Loop (0 to 3)
│  └─ Get Wheel Status
│     ├─ Branch (Is In Contact)
│     │  ├─ True: Print String ("Wheel touching ground")
│     │  └─ False: Print String ("Wheel in air")
```

---

## Additional Notes

### Performance Considerations
- Batch queries are enabled by default for better performance
- Multithreading is enabled by default
- Vehicles automatically sleep when stationary
- Consider LOD systems for distant vehicles

### Thread Safety
- Vehicle simulation runs on the physics thread
- Input methods are thread-safe
- State queries may return slightly stale data due to threading

### Replication
- Basic vehicle state is automatically replicated
- Custom replication can be added by extending `FVehicleReplicatedState`
- Server is authoritative for physics simulation

---

For more information, see:
- [README.md](README.md) - Main documentation
- [GETTING_STARTED.md](GETTING_STARTED.md) - Setup guide
- [Unreal Engine Documentation](https://docs.unrealengine.com/)
