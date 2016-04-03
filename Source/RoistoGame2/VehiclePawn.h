// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Character.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "VehiclePawn.generated.h"

UCLASS()
class AVehiclePawn : public ACharacter
{
        GENERATED_BODY()

    public:
        AVehiclePawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

        virtual void BeginPlay() override;

        virtual void Tick(float DeltaSeconds) override;

        virtual void SetupPlayerInputComponent(UInputComponent *InputComponent) override;

    protected:

        // Components

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Vehicle")
        USpringArmComponent *CameraSpringArmComponent;
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Vehicle")
        UCameraComponent *CameraComponent;

        // Editable stuff

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
        float MaxSpeed;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
        float MaxRotationSpeed;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
        float Acceleration;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
        float RotationAcceleration;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
        float BrakeDeceleration;

        // Current movement

        /** Current vehicle speed */
        UPROPERTY(BlueprintReadOnly, Category="Vehicle")
        float Speed;
        /** Current vehicle movement direction */
        UPROPERTY(BlueprintReadOnly, Category="Vehicle")
        FVector MovementDirection;
        /** Current vehicle yaw rotation (per second) */
        UPROPERTY(BlueprintReadOnly, Category="Vehicle")
        float Rotation;

        // Controls

        bool TurnRight;
        bool TurnLeft;
        bool Accelerate;
        bool Brake;

    private:
        void CalculateSpeed(float deltaTime);
        void CalculateRotation(float deltaTime);
        void CalculateDirection(float deltaTime);

        void StartAccelerating();
        void StopAccelerating();
        void StartBraking();
        void StopBraking();
        void StartTurnLeft();
        void StopTurnLeft();
        void StartTurnRight();
        void StopTurnRight();
};
