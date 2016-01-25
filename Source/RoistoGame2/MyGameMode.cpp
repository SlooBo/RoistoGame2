// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyGameMode.h"
#include "PlayerCar.h"

AMyGameMode::AMyGameMode(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	//Defaults for game mode, use blueprints to override

	/*
	PlayerControllerClass = 
	PlayerStateClass =
	SpectatorClass =
	GhostCharacterClass =
	GameStateClass =
	*/

	startTime = 0;

}

//FString AMyGameMode::GetInGameStateAsString(InGameState state)
//{
//	const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, STRINGIFY(InGameState), true);
//	if (enumptr == NULL)
//	{
//		return FString("Invalid");
//	}
//	return enumptr->GetEnumName((uint8)state);
//}