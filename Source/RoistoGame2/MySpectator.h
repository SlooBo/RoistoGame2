// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "MySpectator.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMySpectator : public ASpectatorPawn
{
	GENERATED_BODY()
public:
	AMySpectator(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void TryRespawn();
	
};
