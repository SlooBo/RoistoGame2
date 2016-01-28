// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "PlayerCar.h"
#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

APlayerCar* Util::GetLocalPlayer(UWorld* world)
{
	return Cast<APlayerCar>(world->GetFirstPlayerController()->GetPawn());
}

APlayerCar* Util::GetPlayerCar(APlayerController* player)
{
	return Cast<APlayerCar>(player->GetPawn());
}

int32 Util::GetNumPlayers(UWorld* world)
{
	int32 numPlayers = 0;

	for (FConstPlayerControllerIterator iter = world->GetPlayerControllerIterator(); iter; ++iter)
		numPlayers++;

	return numPlayers;
}