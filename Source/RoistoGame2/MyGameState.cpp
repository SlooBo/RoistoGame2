// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyGameState.h"


AMyGameState::AMyGameState(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, inGameState);
	DOREPLIFETIME(AMyGameState, teamRaceState);
	DOREPLIFETIME(AMyGameState, stateTimeElapsed);
	DOREPLIFETIME(AMyGameState, stateTimeLength);
	DOREPLIFETIME(AMyGameState, gameTimeElapsed);
	DOREPLIFETIME(AMyGameState, gameTimeLength);
};

int32 AMyGameState::GetStateTimeleft()
{
	return stateTimeLength - stateTimeElapsed;
}

int32 AMyGameState::GetGameTimeleft()
{
	return gameTimeLength - gameTimeElapsed;
}

int32 AMyGameState::GetStateTimeElapsed()
{
	return stateTimeElapsed;
}

int32 AMyGameState::GetGameTimeElapsed()
{
	return gameTimeElapsed;
}

int32 AMyGameState::GetStateTimeLength()
{
	return stateTimeLength;
}

int32 AMyGameState::GetGameTimeLength()
{
	return gameTimeLength;
}