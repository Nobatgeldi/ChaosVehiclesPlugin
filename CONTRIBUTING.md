# Contributing to ChaosVehiclesPlugin

Thank you for your interest in contributing to the ChaosVehiclesPlugin! This document provides guidelines and best practices for contributing to this project.

## Table of Contents
1. [Code of Conduct](#code-of-conduct)
2. [Getting Started](#getting-started)
3. [Development Setup](#development-setup)
4. [Contribution Guidelines](#contribution-guidelines)
5. [Coding Standards](#coding-standards)
6. [Testing](#testing)
7. [Submitting Changes](#submitting-changes)

## Code of Conduct

This project follows the Unreal Engine community standards. Please be respectful and constructive in all interactions.

## Getting Started

Before contributing:

1. **Familiarize yourself with the codebase**
   - Read the [README.md](README.md)
   - Review [GETTING_STARTED.md](GETTING_STARTED.md)
   - Study the [API_REFERENCE.md](API_REFERENCE.md)

2. **Check existing issues**
   - Look for existing issues or feature requests
   - Join discussions on relevant topics
   - Avoid duplicate work

3. **Discuss major changes**
   - Open an issue for significant changes
   - Get feedback before investing time in implementation

## Development Setup

### Prerequisites
- Unreal Engine 5.0 or higher (source build recommended for plugin development)
- Visual Studio 2019 or 2022 (Windows) / Xcode (Mac)
- Git for version control

### Setting Up Development Environment

1. **Clone the repository**
   ```bash
   git clone https://github.com/Nobatgeldi/ChaosVehiclesPlugin.git
   cd ChaosVehiclesPlugin
   ```

2. **Create a test project**
   - Create a new UE5 project
   - Copy the plugin to the project's Plugins folder
   - Generate project files
   - Build the project

3. **Enable debugging**
   - Build in Development Editor configuration
   - Use debug symbols for better debugging experience

## Contribution Guidelines

### Types of Contributions

We welcome:
- **Bug fixes**: Fix issues in existing functionality
- **Features**: Add new vehicle capabilities
- **Performance improvements**: Optimize existing systems
- **Documentation**: Improve or expand documentation
- **Examples**: Add example vehicles or use cases
- **Tests**: Add or improve test coverage

### Before You Start

1. **Fork the repository**
   - Create your own fork on GitHub
   - Clone your fork locally

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   # or
   git checkout -b fix/your-bug-fix
   ```

3. **Keep your fork updated**
   ```bash
   git remote add upstream https://github.com/Nobatgeldi/ChaosVehiclesPlugin.git
   git fetch upstream
   git merge upstream/main
   ```

## Coding Standards

### C++ Style Guide

Follow Epic Games' [Coding Standard](https://docs.unrealengine.com/5.0/en-US/epic-cplusplus-coding-standard-for-unreal-engine/):

#### Naming Conventions
```cpp
// Classes: Prefix with appropriate letter (U, A, F, E, I)
class UChaosVehicleWheel : public UObject {};
class AWheeledVehiclePawn : public APawn {};
struct FWheelStatus {};
enum class EVehicleDifferential {};
interface IVehicleInterface {};

// Member variables: Use descriptive names
float MaxRPM;
bool bAffectedByBrake;  // Boolean prefix with 'b'
TArray<UChaosVehicleWheel*> Wheels;

// Functions: Use verb + noun pattern
void SetThrottleInput(float Value);
float GetForwardSpeed() const;
bool IsOnGround() const;

// Constants: Use all caps with underscores
static const float MAX_WHEEL_SPEED;
```

#### Code Organization
```cpp
// Header file structure
#pragma once

// System includes
#include "CoreMinimal.h"

// Engine includes
#include "GameFramework/Pawn.h"

// Plugin includes
#include "ChaosVehicleMovementComponent.h"

// Generated include (must be last)
#include "WheeledVehiclePawn.generated.h"

// Class declaration
UCLASS()
class CHAOSVEHICLES_API AWheeledVehiclePawn : public APawn
{
    GENERATED_BODY()
    
public:
    // Public methods
    
protected:
    // Protected methods
    
private:
    // Private methods and properties
};
```

#### Comments
```cpp
/**
 * Detailed description of class or function.
 * Can span multiple lines.
 * @param ParamName Description of parameter
 * @return Description of return value
 */
```

### Blueprint Exposure

Make functionality accessible to Blueprints when appropriate:

```cpp
// Functions
UFUNCTION(BlueprintCallable, Category = "Vehicle")
float GetForwardSpeed() const;

// Properties
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
float MaxSpeed;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
float CurrentSpeed;
```

### Performance Considerations

1. **Avoid expensive operations in Tick**
   - Cache values when possible
   - Use timers for periodic updates
   - Consider async operations

2. **Memory management**
   - Use TArray, TMap for dynamic collections
   - Prefer object pooling for frequently created objects
   - Be mindful of object lifetime

3. **Physics threading**
   - Vehicle simulation runs on physics thread
   - Ensure thread safety for shared data
   - Use proper synchronization

## Testing

### Manual Testing

Before submitting changes:

1. **Test basic functionality**
   - Create a test vehicle
   - Test input response
   - Verify physics behavior

2. **Test edge cases**
   - Steep slopes
   - High speeds
   - Multiple vehicles
   - Network conditions (if applicable)

3. **Performance testing**
   - Profile frame times
   - Check for memory leaks
   - Test with multiple vehicles

4. **Cross-platform testing** (if possible)
   - Windows
   - Mac
   - Linux
   - Console platforms

### Debug Visualization

Use built-in debug tools:
```
p.Vehicles.ShowDebug 1
p.Vehicles.ShowSuspensionRaycasts 1
p.Vehicles.ShowWheelForces 1
```

### Test Checklist

- [ ] Code compiles without warnings
- [ ] No runtime errors in editor
- [ ] Changes work as expected
- [ ] Existing functionality not broken
- [ ] Performance not degraded
- [ ] Documentation updated if needed

## Submitting Changes

### Commit Messages

Write clear, descriptive commit messages:

```
Short summary (50 chars or less)

More detailed explanation if needed. Wrap at 72 characters.
Explain what changed and why, not how.

- Bullet points are okay
- Use present tense ("Add feature" not "Added feature")
- Reference issues: "Fixes #123" or "Related to #456"
```

Examples:
```
Add torque vectoring support for AWD vehicles

Implement new torque distribution system that allows
different torque ratios per wheel based on slip conditions.

Fixes #42
```

### Pull Request Process

1. **Prepare your changes**
   - Ensure all tests pass
   - Update documentation
   - Clean up debug code
   - Rebase on latest main if needed

2. **Create pull request**
   - Use descriptive title
   - Fill out PR template
   - Reference related issues
   - Add screenshots/videos if applicable

3. **PR Description should include**
   - What: Brief description of changes
   - Why: Motivation and context
   - How: Technical approach (if complex)
   - Testing: How you tested the changes
   - Screenshots/Videos: Visual changes

4. **Code review**
   - Respond to feedback promptly
   - Make requested changes
   - Update PR with new commits or amend
   - Be open to suggestions

5. **After approval**
   - Squash commits if requested
   - Maintainer will merge

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Performance improvement
- [ ] Documentation update
- [ ] Other (please describe)

## Testing
Describe how you tested these changes

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-reviewed the code
- [ ] Commented complex code sections
- [ ] Updated documentation
- [ ] No new warnings
- [ ] Tested with example vehicles

## Related Issues
Fixes #(issue number)

## Screenshots/Videos
If applicable, add screenshots or videos
```

## Specific Areas for Contribution

### High Priority
- Performance optimizations
- Bug fixes in physics simulation
- Multiplayer/replication improvements
- Documentation improvements

### Feature Ideas
- Advanced tire models
- Weather effects on vehicle handling
- Damage system integration
- Vehicle customization system
- AI driver support
- Additional vehicle types

### Documentation Needs
- More code examples
- Video tutorials
- Blueprint setup guides
- Performance tuning guide
- Troubleshooting guide

## Getting Help

### Resources
- [Unreal Engine Documentation](https://docs.unrealengine.com/)
- [Unreal Engine Forums](https://forums.unrealengine.com/)
- [Chaos Physics Documentation](https://docs.unrealengine.com/5.0/en-US/chaos-physics-overview-for-unreal-engine/)

### Communication
- GitHub Issues: For bugs and feature requests
- GitHub Discussions: For questions and general discussion

## Recognition

Contributors will be recognized in:
- CONTRIBUTORS.md file
- Release notes for significant contributions
- Project documentation

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (Epic Games license terms).

---

Thank you for contributing to ChaosVehiclesPlugin! Your efforts help make vehicle simulation in Unreal Engine better for everyone.
