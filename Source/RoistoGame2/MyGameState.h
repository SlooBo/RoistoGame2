// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "MyGameModeTeamRace.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyGameState : public AGameState
{
	GENERATED_BODY()
public:
	AMyGameState(const FObjectInitializer& objectInitializer);
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
};
