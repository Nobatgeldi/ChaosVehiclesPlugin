# ChaosVehiclesPlugin

[![License](https://img.shields.io/badge/license-Epic%20Games-blue.svg)](LICENSE)
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.x-purple.svg)](https://www.unrealengine.com/)

A comprehensive Unreal Engine plugin that provides a lightweight, high-performance physics-based vehicle simulation system using the Chaos physics engine.

## Overview

Chaos Vehicles is Unreal Engine's modern vehicle physics simulation system built on top of the Chaos physics engine. This plugin provides a flexible and performant framework for creating realistic wheeled and tracked vehicles in your Unreal Engine projects.

## Documentation

- 📖 **[Getting Started Guide](GETTING_STARTED.md)** - Step-by-step tutorial to create your first vehicle
- 📚 **[API Reference](API_REFERENCE.md)** - Complete API documentation for all classes and methods
- 🤝 **[Contributing Guide](CONTRIBUTING.md)** - Guidelines for contributing to the project
- 📝 **[Changelog](CHANGELOG.md)** - Version history and feature documentation

## Features

- **High-Performance Physics**: Leverages the Chaos physics engine for realistic and efficient vehicle simulations
- **Wheeled Vehicle Support**: Full support for cars, motorcycles, and other wheeled vehicles with customizable wheel configurations
- **Tracked Vehicle Support**: Experimental support for tracked vehicles (tanks, bulldozers, etc.)
- **Advanced Suspension System**: Configurable suspension with support for various types including constraint-based suspension
- **Realistic Wheel Physics**: Individual wheel simulation with friction, slip, and contact physics
- **Animation Integration**: Built-in animation nodes for wheel controllers and vehicle animations
- **Differential System**: Support for various differential types (AWD, FWD, RWD)
- **Torque Control**: Advanced torque control system for vehicle dynamics
- **Aerodynamics**: Aerofoil and thrust systems for advanced vehicle behavior
- **Debug Visualization**: Comprehensive debugging tools with multiple debug pages for tuning
- **Blueprint Integration**: Full Blueprint support for vehicle setup and control
- **Multiplayer Ready**: Built-in replication support for networked games

## System Requirements

- **Unreal Engine Version**: 5.0 or higher (recommended: 5.1+)
- **Physics Engine**: Chaos Physics (enabled by default in UE5)
- **Platform Support**: Windows, Mac, Linux, and console platforms supported by Unreal Engine

## Installation

### Method 1: Plugin Installation (Recommended)

1. Clone or download this repository
2. Copy the `ChaosVehiclesPlugin` folder to your project's `Plugins` directory
   ```
   YourProject/
   ├── Plugins/
   │   └── ChaosVehiclesPlugin/
   ```
3. Regenerate project files (right-click on `.uproject` → Generate Visual Studio project files)
4. Open your project in Unreal Engine
5. Enable the plugin: `Edit` → `Plugins` → Search for "ChaosVehiclesPlugin" → Check the enabled box
6. Restart the editor

### Method 2: Engine Installation

1. Copy the plugin to your Unreal Engine installation's plugins directory:
   ```
   [EngineInstallation]/Engine/Plugins/ChaosVehiclesPlugin/
   ```
2. The plugin will be available for all projects

## Quick Start

### Creating a Basic Wheeled Vehicle

1. **Create a Vehicle Pawn**:
   - Create a new Blueprint class based on `AWheeledVehiclePawn`
   - Add a skeletal mesh component for your vehicle body
   - Add a `UChaosWheeledVehicleMovementComponent`

2. **Configure Wheels**:
   - Create wheel Blueprint classes based on `UChaosVehicleWheel`
   - Configure wheel properties (radius, width, friction, etc.)
   - Assign wheels to the vehicle movement component

3. **Set Up Physics**:
   - Ensure your vehicle skeletal mesh has physics enabled
   - Configure mass and center of mass
   - Set up collision

4. **Configure Movement**:
   - Set engine properties (max RPM, torque curve)
   - Configure transmission (gear ratios, clutch)
   - Set up differential type
   - Adjust suspension settings

5. **Test Your Vehicle**:
   - Place your vehicle in the level
   - Set up input bindings for throttle, brake, and steering
   - Play and test!

### Basic Input Setup (Blueprint)

```cpp
// Example C++ input binding in your vehicle pawn class
void AMyVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis("Throttle", this, &AMyVehicle::ApplyThrottle);
    PlayerInputComponent->BindAxis("Steering", this, &AMyVehicle::ApplySteering);
    PlayerInputComponent->BindAxis("Brake", this, &AMyVehicle::ApplyBrake);
}

void AMyVehicle::ApplyThrottle(float Value)
{
    if (UChaosWheeledVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
    {
        VehicleMovement->SetThrottleInput(Value);
    }
}
```

## Architecture

### Module Structure

The plugin consists of two main modules:

#### ChaosVehicles (Runtime)
The core runtime module that handles all vehicle physics simulation and gameplay functionality.

**Key Components**:
- `UChaosVehicleMovementComponent` - Base vehicle movement component
- `UChaosWheeledVehicleMovementComponent` - Wheeled vehicle implementation
- `UChaosTrackedVehicleMovementComponent` - Tracked vehicle implementation (experimental)
- `UChaosVehicleWheel` - Wheel configuration and simulation
- `AWheeledVehiclePawn` - Base pawn class for wheeled vehicles
- `FChaosVehicleManager` - Manages vehicle simulation updates

**Physics Systems**:
- Suspension system with multiple constraint types
- Wheel friction and slip calculation
- Transmission and differential simulation
- Torque control system
- Aerodynamics (aerofoils and thrusters)

#### ChaosVehiclesEditor (Editor Only)
Editor-specific functionality for vehicle setup and debugging.

**Key Components**:
- `AnimGraphNode_WheelController` - Animation graph node for wheel animation
- `AnimGraphNode_StageCoachWheelController` - Specialized wheel controller for stage coach wheels
- Asset type actions for vehicle-related assets
- Vehicle creation factories and utilities

### Core Components

#### UChaosVehicleMovementComponent
Base class for all vehicle movement components. Handles:
- Physics integration with Chaos engine
- Input processing and control
- Replication for multiplayer
- Torque control and stabilization
- Aerodynamics systems

#### UChaosWheeledVehicleMovementComponent
Extends the base movement component with wheeled vehicle functionality:
- Individual wheel simulation
- Suspension raycast/sweep queries
- Differential and transmission
- Steering and brake systems
- Debug visualization

#### UChaosVehicleWheel
Defines individual wheel properties:
- Collision mesh and shape
- Friction coefficients
- Suspension configuration
- Steering and braking capabilities
- Axle assignment

## Usage Examples

### Example 1: Accessing Vehicle State in Blueprint

Use the following Blueprint nodes to access vehicle information:
- `Get Forward Speed` - Current speed in cm/s
- `Get Current Gear` - Active gear number
- `Get Engine RPM` - Current engine RPM
- `Is In Air` - Whether vehicle is airborne

### Example 2: Custom Wheel Configuration (C++)

```cpp
UCLASS()
class UChaosVehicleWheel_RearWheel : public UChaosVehicleWheel
{
    GENERATED_BODY()
    
public:
    UChaosVehicleWheel_RearWheel()
    {
        // Wheel shape
        ShapeRadius = 35.0f;
        ShapeWidth = 25.0f;
        
        // Suspension
        SuspensionMaxRaise = 10.0f;
        SuspensionMaxDrop = 10.0f;
        SuspensionDampingRatio = 0.5f;
        
        // Friction
        FrictionForceMultiplier = 3.0f;
        LateralSlipGraph.EditorCurveData.AddKey(0.0f, 1.0f);
        LateralSlipGraph.EditorCurveData.AddKey(20.0f, 0.9f);
        
        // Configuration
        bAffectedByBrake = true;
        bAffectedByHandbrake = true;
        bAffectedByEngine = true;
        AxleType = EAxleType::Rear;
    }
};
```

### Example 3: Debug Visualization

Enable debug visualization in console:
```
p.Vehicles.ShowDebug 1
p.Vehicles.NextDebugPage
p.Vehicles.ShowSuspensionRaycasts 1
p.Vehicles.ShowWheelForces 1
```

Available debug pages:
- Basic Page: Core vehicle state
- Performance Page: Performance metrics
- Steering Page: Steering system info
- Friction Page: Wheel friction data
- Suspension Page: Suspension state
- Transmission Page: Gear and transmission info

## API Reference

### Key Classes

| Class | Purpose |
|-------|---------|
| `UChaosVehicleMovementComponent` | Base class for vehicle physics simulation |
| `UChaosWheeledVehicleMovementComponent` | Wheeled vehicle implementation |
| `UChaosTrackedVehicleMovementComponent` | Tracked vehicle implementation |
| `UChaosVehicleWheel` | Wheel configuration and simulation |
| `AWheeledVehiclePawn` | Base pawn class for vehicles |
| `UVehicleAnimationInstance` | Animation instance for vehicles |
| `AnimNode_WheelController` | Animation node for wheel rotation |

### Configuration Structures

| Structure | Purpose |
|-----------|---------|
| `FVehicleTorqueControlConfig` | Torque control settings |
| `FWheelStatus` | Runtime wheel state information |
| `FVehicleReplicatedState` | Network replication data |

## Performance Optimization

- **Batch Queries**: Enable `p.Vehicles.BatchQueries 1` for better performance with multiple vehicles
- **Multithreading**: Enabled by default (`p.Vehicles.EnableMultithreading 1`)
- **Sleep System**: Vehicles automatically sleep when stationary to save performance
- **LOD**: Use simpler collision for distant vehicles

## Troubleshooting

### Vehicle Won't Move
- Check that wheels are properly assigned in the movement component
- Verify physics is enabled on the skeletal mesh
- Ensure the vehicle has mass and isn't kinematic
- Check input bindings are correct

### Vehicle Feels Unstable
- Adjust suspension damping ratio
- Lower center of mass
- Increase suspension stiffness
- Reduce wheel friction multipliers

### Poor Network Performance
- Reduce replication frequency for non-critical vehicles
- Use simplified physics for remote vehicles
- Enable relevancy and distance culling

## Contributing

Contributions are welcome! This is an experimental plugin based on Epic Games' Chaos Vehicles system.

### Guidelines
- Follow Unreal Engine coding standards
- Test changes with multiple vehicle configurations
- Update documentation for API changes
- Include examples for new features

## License

Copyright Epic Games, Inc. All Rights Reserved.

This plugin is based on Unreal Engine's Chaos Vehicles system and follows Epic Games' licensing terms.

## Credits

- **Created By**: Epic Games, Inc.
- **Category**: Physics
- **Status**: Experimental

## Additional Resources

- [Unreal Engine Documentation](https://docs.unrealengine.com/)
- [Chaos Physics Overview](https://docs.unrealengine.com/5.0/en-US/chaos-physics-overview-for-unreal-engine/)
- [Vehicle Development Guide](https://docs.unrealengine.com/5.0/en-US/vehicles-in-unreal-engine/)

## Support

For issues, questions, or feature requests, please use the GitHub Issues section of this repository.

---

**Note**: This is an experimental plugin. Features and APIs may change in future releases.
