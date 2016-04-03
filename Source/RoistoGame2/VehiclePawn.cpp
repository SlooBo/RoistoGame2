#include "RoistoGame2.h"
#include "VehiclePawn.h"

AVehiclePawn::AVehiclePawn(const FObjectInitializer &ObjectInitializer)
    : ACharacter(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    CameraSpringArmComponent->AttachTo(RootComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->AttachTo(CameraSpringArmComponent);

    CameraSpringArmComponent->SetRelativeLocation(FVector(-372.f, 0.f, 108.f));
    CameraSpringArmComponent->TargetArmLength = 256.f;

    // We want full control of our rotation
    bUseControllerRotationYaw = false;

    // Defaults properties

    MaxSpeed = 5000.f;
    MaxRotationSpeed = 45.f;
    Acceleration = 500.f;
    RotationAcceleration = 90.f;
    BrakeDeceleration = 3500.f;

    Speed = 0;
    MovementDirection = FVector::ZeroVector;
    Rotation = 0;

    TurnRight = false;
    TurnLeft = false;
    Accelerate = false;
    Brake = false;
}

void AVehiclePawn::BeginPlay()
{
    Super::BeginPlay();

    // Apply our settings to character movement
    GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void AVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    CalculateSpeed(DeltaSeconds);
    CalculateRotation(DeltaSeconds);
    CalculateDirection(DeltaSeconds);

    AddMovementInput(MovementDirection, Speed * DeltaSeconds);

}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent *InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindKey(EKeys::W, IE_Pressed, this, &AVehiclePawn::StartAccelerating);
    InputComponent->BindKey(EKeys::W, IE_Released, this, &AVehiclePawn::StopAccelerating);
    InputComponent->BindKey(EKeys::S, IE_Pressed, this, &AVehiclePawn::StartBraking);
    InputComponent->BindKey(EKeys::S, IE_Released, this, &AVehiclePawn::StopBraking);
    InputComponent->BindKey(EKeys::A, IE_Pressed, this, &AVehiclePawn::StartTurnLeft);
    InputComponent->BindKey(EKeys::A, IE_Released, this, &AVehiclePawn::StopTurnLeft);
    InputComponent->BindKey(EKeys::D, IE_Pressed, this, &AVehiclePawn::StartTurnRight);
    InputComponent->BindKey(EKeys::D, IE_Released, this, &AVehiclePawn::StopTurnRight);
}

void AVehiclePawn::CalculateSpeed(float deltaTime)
{
    if(Accelerate) {
        Speed += Acceleration * deltaTime;
    }
    else if(Brake) {
        Speed -= BrakeDeceleration * deltaTime;
    }
    else {
        Speed -= 1.f * deltaTime;
    }
    Speed = FMath::Clamp(Speed, 0.f, MaxSpeed);
}

void AVehiclePawn::CalculateRotation(float deltaTime)
{
    if(TurnRight) {
        if(Rotation < 0.f)
            Rotation = 0.f;
        Rotation += RotationAcceleration * deltaTime;
    }
    else if(TurnLeft) {
        if(Rotation > 0.f)
            Rotation = 0.f;
        Rotation -= RotationAcceleration * deltaTime;
    }
    else {
        // TODO fade out
        Rotation = 0.f;
    }
    Rotation = FMath::Clamp(Rotation, -MaxRotationSpeed, MaxRotationSpeed);

    FRotator rot = GetActorRotation();
    rot.Yaw += Rotation * deltaTime;
    SetActorRotation(rot);
}

void AVehiclePawn::CalculateDirection(float deltaTime)
{
    FRotator rot(0.f, GetActorRotation().Yaw, 0.f);
    // Get forward vector of rot
    FVector dir = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
    MovementDirection = dir;
}

void AVehiclePawn::StartAccelerating()
{
    Accelerate = true;
}

void AVehiclePawn::StopAccelerating()
{
    Accelerate = false;
}

void AVehiclePawn::StartBraking()
{
    Brake = true;
}

void AVehiclePawn::StopBraking()
{
    Brake = false;
}

void AVehiclePawn::StartTurnLeft()
{
    TurnLeft = true;
}

void AVehiclePawn::StopTurnLeft()
{
    TurnLeft = false;
}

void AVehiclePawn::StartTurnRight()
{
    TurnRight = true;
}

void AVehiclePawn::StopTurnRight()
{
    TurnRight = false;
}
