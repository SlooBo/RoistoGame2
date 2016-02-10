// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPlayerController.h"
#include "BasePawn.generated.h"

UCLASS()
class ROISTOGAME2_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& DmgType) override;

	void DelayedDestroy();

protected:


	UFUNCTION(Reliable, NetMulticast)
	void OnDeath(AMyPlayerController* damageSource = NULL);
	virtual void OnDeath_Implementation(AMyPlayerController* damageSource = NULL);

	void DelayedDestroy(FTimerHandle& timerHandle);
	
};
