// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "CarMovementComponent.h"
#include "MyPlayerController.h"
#include "PlayerCarCode.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API APlayerCarCode : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCarCode(const FObjectInitializer& ObjectInitializer);

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

	//const UBoxComponent* getHitBox();

protected:

	UBoxComponent* MyHitBox;

	class UCarMovementComponent* MyMovementComponent;
};

