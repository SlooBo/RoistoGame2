// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "CarMovementComponent.h"
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
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	//MovementControls
	void MoveForward(float AxisValue);
	void Turn(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* CarMesh;

	UStaticMeshComponent* WheelMesh;

	//const UBoxComponent* getHitBox();
	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Reached checkpoint"), Category = "Gameplay | Player")
	void addCheckpoint(int32 checkpoint);
	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Survived lap"), Category = "Gameplay|Player")
	void addLap();

protected:

	UBoxComponent* MyHitBox;
	bool Checkpoint1;
	bool Checkpoint2;
	bool Checkpoint3;

	class UCarMovementComponent* MyMovementComponent;
};

