// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "BuilderPawn.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API ABuilderPawn : public ABasePawn
{
	GENERATED_BODY()

	ABuilderPawn(const FObjectInitializer& ObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	
protected:

	UBoxComponent* MyHitBox;


};
