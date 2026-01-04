# Getting Started with ChaosVehiclesPlugin

This guide will help you create your first vehicle using the Chaos Vehicles Plugin.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Creating Your First Vehicle](#creating-your-first-vehicle)
3. [Vehicle Setup Steps](#vehicle-setup-steps)
4. [Input Configuration](#input-configuration)
5. [Common Issues and Solutions](#common-issues-and-solutions)

## Prerequisites

Before you begin, ensure you have:
- Unreal Engine 5.0 or higher installed
- ChaosVehiclesPlugin installed and enabled in your project
- A vehicle skeletal mesh with proper bone hierarchy
- Basic understanding of Unreal Engine Blueprints or C++

## Creating Your First Vehicle

### Step 1: Prepare Your Vehicle Mesh

1. **Import your vehicle skeletal mesh** into your project
   - The mesh should have bones for the body and each wheel
   - Wheel bones should be named clearly (e.g., Wheel_FL, Wheel_FR, Wheel_RL, Wheel_RR)
   - Ensure the mesh is facing forward in the positive X direction

2. **Set up physics asset**
   - Right-click on your skeletal mesh → Create → Physics Asset
   - Configure the physics bodies for the vehicle body
   - Set the root body to "Simulated"
   - Configure mass (typical car: 1000-2000 kg)

### Step 2: Create Vehicle Blueprint

1. **Create the Vehicle Pawn**:
   - In Content Browser: Right-click → Blueprint Class
   - Search for and select `WheeledVehiclePawn` as the parent class
   - Name it (e.g., `BP_MyVehicle`)

2. **Configure the Skeletal Mesh Component**:
   - Open your vehicle Blueprint
   - Select the `Mesh` component
   - Set the Skeletal Mesh asset to your imported mesh
   - Adjust the transform if needed (ensure it's positioned correctly)

3. **Configure Vehicle Movement Component**:
   - Select the `VehicleMovementComponent`
   - This is where you'll configure all vehicle physics parameters

### Step 3: Create Wheel Blueprints

You'll typically need 2-4 wheel Blueprint classes (front and rear, possibly left and right):

1. **Create Front Wheel Blueprint**:
   - Right-click → Blueprint Class
   - Search for `ChaosVehicleWheel`
   - Name it `BP_FrontWheel`

2. **Configure Front Wheel Properties**:
   ```
   Shape:
   - Shape Radius: 35.0 (cm)
   - Shape Width: 20.0 (cm)
   
   Wheel:
   - Affected By Brake: true
   - Affected By Handbrake: false
   - Affected By Engine: true (for FWD/AWD)
   - Affected By Steering: true
   - Max Steer Angle: 50.0 (degrees)
   - Axle Type: Front
   
   Suspension:
   - Suspension Max Raise: 10.0
   - Suspension Max Drop: 10.0
   - Suspension Damping Ratio: 0.5
   - Suspension Natural Frequency: 7.0
   
   Friction:
   - Friction Force Multiplier: 2.0
   ```

3. **Create Rear Wheel Blueprint**:
   - Repeat the process for `BP_RearWheel`
   - Set `Affected By Steering: false`
   - Set `Affected By Handbrake: true`
   - Set `Axle Type: Rear`

### Step 4: Configure Wheel Setup

Back in your vehicle Blueprint (`BP_MyVehicle`):

1. **Add Wheels to Vehicle Movement Component**:
   - Select `VehicleMovementComponent`
   - Find the `Wheels` array property
   - Add 4 elements (for a typical 4-wheeled vehicle)

2. **Configure Each Wheel**:
   
   **Wheel 0 (Front Left)**:
   ```
   - Wheel Class: BP_FrontWheel
   - Bone Name: Wheel_FL (match your skeletal mesh)
   - Location: (150, -70, 0) (adjust to match your mesh)
   ```
   
   **Wheel 1 (Front Right)**:
   ```
   - Wheel Class: BP_FrontWheel
   - Bone Name: Wheel_FR
   - Location: (150, 70, 0)
   ```
   
   **Wheel 2 (Rear Left)**:
   ```
   - Wheel Class: BP_RearWheel
   - Bone Name: Wheel_RL
   - Location: (-150, -70, 0)
   ```
   
   **Wheel 3 (Rear Right)**:
   ```
   - Wheel Class: BP_RearWheel
   - Bone Name: Wheel_RR
   - Location: (-150, 70, 0)
   ```

### Step 5: Configure Engine and Transmission

In the `VehicleMovementComponent`:

1. **Engine Setup**:
   ```
   Max RPM: 6000
   MOI (Moment of Inertia): 1.0
   Damping Rate (Zero Throttle Clutch Engaged): 0.15
   Damping Rate (Zero Throttle Clutch Disengaged): 0.35
   ```

2. **Torque Curve** (Engine Setup → Torque Curve):
   - Add curve points to define engine torque across RPM range
   - Example:
     - (0 RPM, 200 Nm)
     - (3000 RPM, 350 Nm)
     - (5500 RPM, 300 Nm)
     - (6000 RPM, 250 Nm)

3. **Transmission Setup**:
   ```
   Transmission Type: Automatic (or Manual)
   Gear Change Time: 0.5
   Final Ratio: 3.08
   
   Forward Gear Ratios:
   - Gear 1: 3.5
   - Gear 2: 2.5
   - Gear 3: 1.8
   - Gear 4: 1.3
   - Gear 5: 1.0
   - Gear 6: 0.8
   
   Reverse Gear Ratio: -3.5
   ```

4. **Differential Setup**:
   ```
   Differential Type: AllWheelDrive (or FrontWheelDrive/RearWheelDrive)
   ```

### Step 6: Configure Mass and Center of Mass

1. **In the Mesh Component → Physics**:
   ```
   Simulate Physics: true
   Mass (kg): 1500
   Linear Damping: 0.01
   Angular Damping: 0.01
   ```

2. **Adjust Center of Mass** (if needed):
   - Open the Physics Asset
   - Select the main body
   - Adjust COM offset (usually lower for better stability)

### Step 7: Set Up Input

#### Blueprint Method:

1. **Project Settings → Input**:
   - Add Axis Mappings:
     - `Throttle`: W key (Scale: 1.0), S key (Scale: -1.0)
     - `Steering`: A key (Scale: -1.0), D key (Scale: 1.0)
     - `Brake`: Spacebar (Scale: 1.0)

2. **In Vehicle Blueprint Event Graph**:
   
   Add these nodes:

   ```
   Event Tick
   ├─ Get Player Controller
   ├─ Get Input Axis Value (Throttle)
   └─ Set Throttle Input (VehicleMovementComponent)
   
   Event Tick
   ├─ Get Player Controller
   ├─ Get Input Axis Value (Steering)
   └─ Set Steering Input (VehicleMovementComponent)
   
   Event Tick
   ├─ Get Player Controller
   ├─ Get Input Axis Value (Brake)
   └─ Set Brake Input (VehicleMovementComponent)
   ```

#### C++ Method:

```cpp
void AMyVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Bind axis inputs
    PlayerInputComponent->BindAxis("Throttle", this, &AMyVehicle::MoveForward);
    PlayerInputComponent->BindAxis("Steering", this, &AMyVehicle::MoveRight);
    PlayerInputComponent->BindAxis("Brake", this, &AMyVehicle::ApplyBrake);
    
    // Bind action inputs
    PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AMyVehicle::OnHandbrakePressed);
    PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AMyVehicle::OnHandbrakeReleased);
}

void AMyVehicle::MoveForward(float Value)
{
    GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void AMyVehicle::MoveRight(float Value)
{
    GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void AMyVehicle::ApplyBrake(float Value)
{
    GetVehicleMovementComponent()->SetBrakeInput(Value);
}

void AMyVehicle::OnHandbrakePressed()
{
    GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AMyVehicle::OnHandbrakeReleased()
{
    GetVehicleMovementComponent()->SetHandbrakeInput(false);
}
```

### Step 8: Test Your Vehicle

1. **Place the vehicle in your level**
   - Drag `BP_MyVehicle` into the level
   - Position it above the ground (to account for suspension drop)

2. **Set as player start** (for testing):
   - Select the vehicle
   - In Details → Pawn → Auto Possess Player: Player 0

3. **Play and test**:
   - Press Play (PIE)
   - Use W/S for throttle/brake, A/D for steering

## Input Configuration

### Recommended Input Setup

**Project Settings → Input**:

#### Axis Mappings:
| Name | Key | Scale |
|------|-----|-------|
| Throttle | W | 1.0 |
| Throttle | S | -1.0 |
| Throttle | Gamepad Left Trigger | 1.0 |
| Steering | A | -1.0 |
| Steering | D | 1.0 |
| Steering | Gamepad Left Thumbstick X-Axis | 1.0 |
| Brake | Space | 1.0 |
| Brake | Gamepad Right Trigger | 1.0 |

#### Action Mappings:
| Name | Key |
|------|-----|
| Handbrake | Left Shift |
| Handbrake | Gamepad Face Button Bottom |

## Common Issues and Solutions

### Issue: Vehicle Falls Through Ground
**Solution**: 
- Ensure collision is enabled on the level geometry
- Check that the vehicle's physics asset has valid collision shapes
- Verify "Simulate Physics" is enabled on the mesh component

### Issue: Vehicle Doesn't Respond to Input
**Solution**:
- Check input bindings are correct in Project Settings
- Verify the vehicle is possessed by a player controller
- Ensure the movement component is properly initialized
- Check console for any error messages

### Issue: Wheels Don't Touch Ground
**Solution**:
- Adjust wheel bone locations in the vehicle movement component
- Check suspension max drop value (increase if needed)
- Verify wheel bone names match the skeletal mesh

### Issue: Vehicle Flips Over Easily
**Solution**:
- Lower the center of mass in the physics asset
- Increase suspension damping ratio
- Reduce suspension natural frequency
- Widen the wheel track (distance between left/right wheels)

### Issue: Wheels Spin Without Moving
**Solution**:
- Increase friction force multiplier on wheels
- Check that wheels are marked as "Affected By Engine"
- Verify differential type is set correctly
- Reduce engine torque or adjust gear ratios

### Issue: Steering Too Sensitive or Not Responsive
**Solution**:
- Adjust "Max Steer Angle" on front wheels
- Modify steering curve if using speed-based steering
- Check input axis scale values
- Add interpolation to steering input for smoother response

### Issue: Vehicle Bounces Excessively
**Solution**:
- Increase suspension damping ratio (0.5-0.7 typical)
- Lower suspension natural frequency
- Reduce suspension max raise/drop values

## Next Steps

Now that you have a basic vehicle working:

1. **Tune handling**: Adjust suspension, friction, and mass for desired feel
2. **Add visual effects**: Wheel dust, skid marks, engine sounds
3. **Implement advanced features**: Speed-based steering, traction control, ABS
4. **Optimize performance**: LODs, distance culling, simplified physics for AI vehicles
5. **Polish**: Camera shake, motion blur, HUD elements

For more advanced topics, see:
- [API_REFERENCE.md](API_REFERENCE.md) - Detailed API documentation
- [EXAMPLES.md](EXAMPLES.md) - Advanced examples and use cases
- [README.md](README.md) - Main plugin documentation

## Additional Resources

- [Unreal Engine Vehicle Documentation](https://docs.unrealengine.com/5.0/en-US/vehicles-in-unreal-engine/)
- [Physics Asset Tool](https://docs.unrealengine.com/5.0/en-US/physics-asset-editor-in-unreal-engine/)
- [Animation Blueprint for Vehicles](https://docs.unrealengine.com/5.0/en-US/animation-blueprints-in-unreal-engine/)

---

**Happy vehicle building!** 🚗
