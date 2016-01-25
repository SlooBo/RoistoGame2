// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CarMovementComponent.h"
#include "PlayerCar.generated.h"

UCLASS()
class ROISTOGAME2_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	//MovementControls
	void MoveForward(float AxisValue);
	void Turn(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* CarMesh;

	UStaticMeshComponent* WheelMesh;

	class UCarMovementComponent* MyMovementComponent;
};
