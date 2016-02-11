// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyGameState.h"


AMyGameState::AMyGameState(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*DOREPLIFETIME(ACMGameState, inGameState);
	DOREPLIFETIME(ACMGameState, huntGameState);
	DOREPLIFETIME(ACMGameState, stateTimeElapsed);
	DOREPLIFETIME(ACMGameState, stateTimeLength);
	DOREPLIFETIME(ACMGameState, gameTimeElapsed);
	DOREPLIFETIME(ACMGameState, gameTimeLength);*/
};