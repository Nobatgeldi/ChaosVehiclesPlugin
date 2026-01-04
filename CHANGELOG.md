# Changelog

All notable changes to the ChaosVehiclesPlugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - Current Release

### Overview
First documented release of the ChaosVehiclesPlugin for Unreal Engine 5.x

### Features

#### Core Vehicle System
- **Wheeled Vehicle Support**: Full implementation of wheeled vehicle physics using Chaos engine
- **Tracked Vehicle Support**: Experimental tracked vehicle movement component
- **Physics Simulation**: High-performance vehicle simulation integrated with Chaos physics

#### Movement Components
- `UChaosVehicleMovementComponent`: Base vehicle movement with torque control and aerodynamics
- `UChaosWheeledVehicleMovementComponent`: Wheeled vehicle implementation with suspension and differential
- `UChaosTrackedVehicleMovementComponent`: Experimental tracked vehicle support

#### Wheel System
- Individual wheel simulation with configurable properties
- Multiple suspension types (raycast, spherecast, shapecast)
- Friction and slip calculation
- Wheel animation support

#### Mechanical Systems
- **Engine**: Configurable torque curves, RPM limits, and inertia
- **Transmission**: Multiple gear ratios with automatic or manual shifting
- **Differential**: Support for AWD, FWD, and RWD configurations
- **Steering**: Angle-based steering with configurable response
- **Brakes**: Individual wheel brake control with handbrake support

#### Advanced Features
- **Torque Control**: Yaw, pitch, and roll torque control for vehicle stability
- **Aerodynamics**: Aerofoil and thruster systems
- **Multiplayer**: Built-in replication support
- **Debug Visualization**: Comprehensive debug display with multiple pages

#### Animation
- `AnimNode_WheelController`: Animation node for wheel rotation
- `AnimNode_StageCoachWheelController`: Specialized controller for stage coach wheels
- `UVehicleAnimationInstance`: Vehicle-specific animation instance

#### Editor Tools
- Asset type actions for vehicle assets
- Factory classes for creating vehicle components
- Animation graph nodes for vehicle animation

### Technical Details

#### Module Structure
- **ChaosVehicles** (Runtime): Core vehicle simulation module
  - Loading Phase: PreDefault
  - Dependencies: Core, CoreUObject, Engine, EngineSettings, RenderCore, AnimGraphRuntime, RHI, ChaosVehiclesCore, ChaosVehiclesEngine

- **ChaosVehiclesEditor** (Editor): Editor-only functionality
  - Loading Phase: PreDefault
  - Dependencies: Core, CoreUObject, Slate, SlateCore, Engine, EditorFramework, UnrealEd, PropertyEditor, AnimGraphRuntime, AnimGraph, BlueprintGraph, ToolMenus, PhysicsCore, ChaosVehiclesCore, ChaosVehiclesEngine, ChaosVehicles

#### Performance
- Multithreading enabled by default
- Batch query support for improved performance
- Automatic vehicle sleep when stationary
- Efficient physics integration with Chaos engine

### Known Issues
- Tracked vehicle support is experimental and API may change
- Some debug visualizations may impact performance when enabled

### Compatibility
- **Unreal Engine Version**: 5.0+
- **Physics Engine**: Chaos Physics (required)
- **Platforms**: Windows, Mac, Linux, and console platforms supported by Unreal Engine

### Documentation
- README.md: Main project documentation with overview and features
- GETTING_STARTED.md: Step-by-step tutorial for creating first vehicle
- API_REFERENCE.md: Comprehensive API documentation
- CONTRIBUTING.md: Guidelines for contributing to the project

---

## Future Roadmap

### Planned Features
- Enhanced tracked vehicle support
- Advanced tire models
- Weather effects on handling
- Damage system integration
- AI driver support
- Additional vehicle types (boats, aircraft)

### Under Consideration
- Vehicle customization system
- Performance profiling tools
- Additional debug visualizations
- More example vehicles

---

## Version History

### [1.0.0] - 2024
- Initial documented release
- Core wheeled vehicle functionality
- Experimental tracked vehicle support
- Comprehensive documentation

---

## How to Report Issues

If you encounter any issues or have feature requests:

1. Check existing GitHub Issues
2. Create a new issue with:
   - Clear description of the problem
   - Steps to reproduce
   - Expected vs actual behavior
   - Unreal Engine version
   - Platform information
   - Screenshots/videos if applicable

---

## Credits

**Original Authors**: Epic Games, Inc.

**Contributors**: See CONTRIBUTORS.md

---

## License

Copyright Epic Games, Inc. All Rights Reserved.

This plugin follows Epic Games' licensing terms for Unreal Engine plugins.
